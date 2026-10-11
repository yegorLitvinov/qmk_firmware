// Copyright 2026 Egor
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap.h"
#include "keymap_russian.h"
#include "dynamic_keymap.h"
#include "nvm_via.h"
#include "transport.h"
#include "usb_device_state.h"
#include "wireless.h"

#define LANGUAGE_TAP_DELAY 30
#define CONNECTION_SETTLE_DELAY 500
#define VIA_LAYOUT_VERSION 2

static uint8_t     english_symbols_held;
static uint16_t    backspace_output;
static uint8_t     suppressed_shift_mods;
static bool        connection_sync_pending;
static bool        host_connected;
static uint32_t    connection_timer;
static transport_t last_transport;

static const uint16_t PROGMEM english_symbols[] = {
    KC_HASH, KC_CIRC, KC_LCBR, KC_RCBR, KC_GRV, KC_DLR, KC_BSLS, KC_ASTR, KC_COLN, KC_SCLN, KC_AMPR, KC_PIPE, KC_TILD, KC_AT, KC_LT, KC_LBRC, KC_RBRC, KC_GT, KC_COMM, KC_DOT, KC_PERC, KC_QUOT, KC_QUES,
};

static_assert(ARRAY_SIZE(english_symbols) == EN_QUES - EN_HASH + 1, "English symbol keycodes must match their outputs");

static void select_input_source(bool russian) {
    // The selector must work even while Command, Option, or Shift is held.
    const uint8_t mods         = get_mods();
    const uint8_t weak_mods    = get_weak_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    clear_mods();
    clear_oneshot_mods();
    set_weak_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
    send_keyboard_report();
    wait_ms(10);
    tap_code_delay(russian ? KC_2 : KC_1, LANGUAGE_TAP_DELAY);
    clear_weak_mods();
    send_keyboard_report();
    // Allow macOS to apply the new input source before sending a symbol.
    wait_ms(LANGUAGE_TAP_DELAY);

    set_mods(mods);
    set_weak_mods(weak_mods);
    set_oneshot_mods(oneshot_mods);
    send_keyboard_report();
}

static void set_language(bool russian) {
    // Velvet's language keys also leave any held navigation/symbol layer.
    layer_move(russian ? RU_BASE : EN_BASE);
    // English symbols may overlap. Restore Russian only after the last release.
    select_input_source(russian && english_symbols_held == 0);
}

static void schedule_connection_sync(void) {
    layer_clear();
    default_layer_set(1UL << EN_BASE);
    english_symbols_held  = 0;
    backspace_output      = KC_NO;
    suppressed_shift_mods = 0;
    caps_word_off();
    connection_sync_pending = true;
    connection_timer        = timer_read32();
}

void keyboard_post_init_user(void) {
    default_layer_set(1UL << EN_BASE);
}

void wireless_enter_connected_kb(uint8_t host_idx) {
    if (get_transport() & TRANSPORT_WIRELESS) {
        schedule_connection_sync();
    }
}

void matrix_scan_user(void) {
    const transport_t transport = get_transport();
    const bool        connected = transport == TRANSPORT_USB ? usb_device_state_get_configure_state() == USB_DEVICE_STATE_CONFIGURED : (transport & TRANSPORT_WIRELESS) && wireless_get_state() == WT_CONNECTED;

    if (connected && (!host_connected || transport != last_transport)) {
        schedule_connection_sync();
    } else if (!connected) {
        connection_sync_pending = false;
    }
    host_connected = connected;
    last_transport = transport;

    if (connection_sync_pending && timer_elapsed32(connection_timer) >= CONNECTION_SETTLE_DELAY) {
        connection_sync_pending = false;
        set_language(false);
    }
}

void via_init_kb(void) {
    uint8_t version = 0;
    nvm_via_read_custom_config(&version, 0, sizeof(version));
    if (version == 1) {
        // Fix the old Russian question mark without overwriting VIA edits.
        if (dynamic_keymap_get_keycode(SYM_RU, 2, 1) == RU_QUES) {
            dynamic_keymap_set_keycode(SYM_RU, 2, 1, EN_QUES);
        }
    } else if (version != VIA_LAYOUT_VERSION) {
        // The old five-layer map and macro offsets cannot be reused.
        via_eeprom_set_valid(false);
    }
    if (version != VIA_LAYOUT_VERSION) {
        version = VIA_LAYOUT_VERSION;
        nvm_via_update_custom_config(&version, 0, sizeof(version));
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && connection_sync_pending && host_connected) {
        connection_sync_pending = false;
        set_language(false);
    }

    if (keycode == LANG_SWITCH) {
        if (record->event.pressed) {
            caps_word_off();
            set_language(!layer_state_is(RU_BASE));
        }
        return false;
    }

    if (keycode >= EN_HASH && keycode <= EN_QUES) {
        const uint16_t output = pgm_read_word(&english_symbols[keycode - EN_HASH]);
        if (record->event.pressed) {
            caps_word_off();
            if (english_symbols_held++ == 0 && layer_state_is(RU_BASE)) {
                select_input_source(false);
            }
            register_code16(output);
        } else {
            unregister_code16(output);
            if (english_symbols_held > 0 && --english_symbols_held == 0 && layer_state_is(RU_BASE)) {
                select_input_source(true);
            }
        }
        return false;
    }

    if (backspace_output == KC_DEL && (keycode == KC_LSFT || keycode == KC_RSFT)) {
        // Track physical Shift releases so releasing Delete cannot leave Shift stuck.
        if (record->event.pressed) {
            suppressed_shift_mods |= MOD_BIT(keycode);
        } else {
            suppressed_shift_mods &= ~MOD_BIT(keycode);
        }
        return false;
    }

    if (keycode == BSPC_DEL) {
        if (record->event.pressed) {
            const uint8_t shifts  = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
            backspace_output      = shifts ? KC_DEL : KC_BSPC;
            suppressed_shift_mods = get_mods() & MOD_MASK_SHIFT;
            del_mods(MOD_MASK_SHIFT);
            del_weak_mods(MOD_MASK_SHIFT);
            set_oneshot_mods(get_oneshot_mods() & ~MOD_MASK_SHIFT);
            register_code(backspace_output);
        } else {
            unregister_code(backspace_output);
            add_mods(suppressed_shift_mods);
            suppressed_shift_mods = 0;
            backspace_output      = KC_NO;
            send_keyboard_report();
        }
        return false;
    }

    return true;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (combo_index == RUSSIAN_HA || combo_index == RUSSIAN_HARD_SIGN) {
        return get_highest_layer(layer_state | default_layer_state) == RU_BASE;
    }
    // Preserve normal behavior of these keys on the unchanged K11 layer.
    return !layer_state_is(K11_MEDIA);
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case BSPC_DEL:
        case KC_UNDS:
            return true;
        default:
            // Russian letters also use punctuation keycodes (ж, э, б, ю, х, ъ, ё).
            if (layer_state_is(RU_BASE) && (keycode == RU_ZHE || keycode == RU_E || keycode == RU_BE || keycode == RU_YU || keycode == RU_HA || keycode == RU_HARD || keycode == RU_YO)) {
                add_weak_mods(MOD_BIT(KC_LSFT));
                return true;
            }
            return false;
    }
}
