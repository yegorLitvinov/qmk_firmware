/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "keymap.h"
#include "keymap_russian.h"

#define APPS MO(APPS_NAV)
#define NUMS MO(NUM_MEDIA)
#define MEDIA MO(K11_MEDIA)
#define HYPER(key) LGUI(LCTL(LALT(key)))

// Physical thumbs, left to right: Command, Space, Right Control, Symbols.
// The physical Command keys hold Apps/Nav; the right B switches EN/RU.
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [EN_BASE] = LAYOUT_69_ansi(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,       KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,           KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    BSPC_DEL,KC_RBRC, KC_BSLS,           KC_DEL,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,       KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,  NUMS,              MEDIA,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LANG_SWITCH,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        NUMS,    KC_LALT, APPS,                     KC_LGUI,         KC_SPC,     KC_RCTL,          MO(SYM_EN),       APPS,             KC_LEFT, KC_DOWN, KC_RGHT),

    [RU_BASE] = LAYOUT_69_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, RU_SHTI, RU_TSE,  RU_U,    RU_KA,   RU_IE,   RU_EN,   RU_GHE,  RU_SHA,  RU_SHCH, RU_ZE,   _______, _______, _______,          _______,
        _______, RU_EF,   RU_YERU, RU_VE,   RU_A,    RU_PE,             RU_ER,   RU_O,    RU_EL,   RU_DE,   RU_ZHE,  _______, _______,          _______,
        _______,          RU_YA,   RU_CHE,  RU_ES,   RU_EM,   RU_I,    _______, RU_TE,   RU_SOFT, RU_BE,   RU_YU,   RU_E,    _______, _______,
        _______, _______, _______,                   _______,         _______, _______,          MO(SYM_RU),       _______,          _______, _______, _______),

    [SYM_EN] = LAYOUT_69_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_HASH, KC_CIRC, KC_EQL,  KC_DQUO, KC_LCBR, KC_RCBR, KC_GRV,  KC_EXLM, KC_DLR,  KC_BSLS, _______, _______, _______,          _______,
        _______, KC_QUES, KC_ASTR, KC_UNDS, KC_COLN, KC_LPRN,          KC_RPRN, KC_SCLN, KC_MINS, KC_AMPR, KC_PIPE, _______, _______,          _______,
        _______,          KC_TILD, KC_PLUS, KC_AT,   KC_LT,   KC_LBRC, _______, KC_RBRC, KC_GT,   KC_COMM, KC_DOT,  KC_SLSH, _______, _______,
        _______, _______, KC_PERC,                   _______,         _______, _______,          _______,          KC_QUOT,          _______, _______, _______),

    [SYM_RU] = LAYOUT_69_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, EN_HASH, EN_CIRC, RU_EQL,  RU_DQUO, EN_LCBR, EN_RCBR, EN_GRV,  RU_EXLM, EN_DLR,  EN_BSLS, _______, _______, _______,          _______,
        _______, EN_QUES, EN_ASTR, RU_UNDS, EN_COLN, RU_LPRN,          RU_RPRN, EN_SCLN, RU_MINS, EN_AMPR, EN_PIPE, _______, _______,          _______,
        _______,          EN_TILD, RU_PLUS, EN_AT,   EN_LT,   EN_LBRC, _______, EN_RBRC, EN_GT,   EN_COMM, EN_DOT,  RU_SLSH, _______, _______,
        _______, _______, EN_PERC,                   _______,         _______, _______,          _______,          EN_QUOT,          _______, _______, _______),

    [APPS_NAV] = LAYOUT_69_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_NO,   HYPER(KC_Q), HYPER(KC_W), HYPER(KC_E), HYPER(KC_R), HYPER(KC_T), RALT(KC_LEFT), KC_PGDN, KC_PGUP, RALT(KC_RGHT), KC_NO, KC_NO, _______, _______, _______,
        KC_NO,   HYPER(KC_A), HYPER(KC_S), HYPER(KC_D), HYPER(KC_F), HYPER(KC_G), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, _______, _______,
        KC_NO,   HYPER(KC_Z), HYPER(KC_X), HYPER(KC_C), HYPER(KC_V), LGUI(LSFT(KC_5)), _______, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LGUI(KC_RGHT), KC_NO, KC_NO, _______,
        KC_NO,   KC_NO,    _______,                   KC_NO,           KC_NO,   KC_NO,             KC_NO,             _______,          _______, _______, _______),

    [NUM_MEDIA] = LAYOUT_69_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,   BT_HST1, BT_HST2, BT_HST3, KC_NO,   KC_NO,   KC_NO,   _______, _______,          _______,
        KC_NO,   KC_0,    KC_4,    KC_5,    KC_6,    KC_NO,            KC_MPLY, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,   KC_NO,   _______,          _______,
        KC_NO,            KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO,   _______, KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_NO,   _______,
        _______, KC_NO,   KC_NO,                      KC_NO,           _______, KC_NO,             KC_NO,             KC_NO,             _______, _______, _______),

    [K11_MEDIA] = LAYOUT_69_ansi(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_MCTRL, KC_LNPAD,UG_VALD, UG_VALU,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            UG_TOGG,
        _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,   _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,            KC_INS,
        UG_TOGG, UG_NEXT,  UG_VALU,  UG_HUEU, UG_SATU, UG_SPDU,           _______, _______, _______, _______,  _______,  _______,  _______,            KC_END,
        _______,           UG_PREV,  UG_VALD, UG_HUED, UG_SATD, UG_SPDD,  _______, _______, _______, _______,  _______,  _______,  _______,  KC_PGUP,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______,  KC_PGDN,  _______)
};

const uint16_t PROGMEM russian_ha[]        = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM russian_hard_sign[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM spotlight[]         = {KC_LGUI, KC_SPC, COMBO_END};
const uint16_t PROGMEM caps_word[]         = {KC_LSFT, KC_RSFT, COMBO_END};

combo_t key_combos[] = {
    [RUSSIAN_HA]        = COMBO(russian_ha, RU_HA),
    [RUSSIAN_HARD_SIGN] = COMBO(russian_hard_sign, RU_HARD),
    [SPOTLIGHT]         = COMBO(spotlight, LGUI(KC_SPC)),
    [CAPS_WORD]         = COMBO(caps_word, CW_TOGG),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [EN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [RU_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [SYM_EN] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [SYM_RU] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [APPS_NAV] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [NUM_MEDIA] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [K11_MEDIA] = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
};
#endif
// clang-format on
