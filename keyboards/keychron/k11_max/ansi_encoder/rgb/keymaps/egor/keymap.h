// Copyright 2026 Egor
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    EN_BASE,
    RU_BASE,
    SYM_EN,
    SYM_RU,
    APPS_NAV,
    NUM_MEDIA,
    K11_MEDIA,
};

enum combos {
    RUSSIAN_HA,
    RUSSIAN_HARD_SIGN,
    SPOTLIGHT,
    CAPS_WORD,
};

// Keep Keychron's existing VIA custom keycodes at indexes 0–15.
enum custom_keycodes {
    LANG_SWITCH = NEW_SAFE_RANGE,
    BSPC_DEL,
    EN_HASH,
    EN_CIRC,
    EN_LCBR,
    EN_RCBR,
    EN_GRV,
    EN_DLR,
    EN_BSLS,
    EN_ASTR,
    EN_COLN,
    EN_SCLN,
    EN_AMPR,
    EN_PIPE,
    EN_TILD,
    EN_AT,
    EN_LT,
    EN_LBRC,
    EN_RBRC,
    EN_GT,
    EN_COMM,
    EN_DOT,
    EN_PERC,
    EN_QUOT,
    EN_QUES,
};

static_assert((uint16_t)EN_QUES <= (uint16_t)QK_KB_MAX, "Custom keycodes exceed VIA's keyboard keycode range");
