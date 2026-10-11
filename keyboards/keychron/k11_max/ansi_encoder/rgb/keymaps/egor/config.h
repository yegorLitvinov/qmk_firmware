// Copyright 2026 Egor
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define KEYCHRON_OS_SWITCH_DISABLE
#define DYNAMIC_KEYMAP_LAYER_COUNT 7
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 1

// Resolve physical combos against the base layout, including on other layers.
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_SHOULD_TRIGGER
#define COMBO_TERM 50

// Home replaces Fn as the key for the stock K11 controls and factory reset.
#undef FN_KEY_1
#define FN_KEY_1 MO(6)
// Z is the previous lighting effect while Home is held.
#define FN_Z_KEY UG_PREV
