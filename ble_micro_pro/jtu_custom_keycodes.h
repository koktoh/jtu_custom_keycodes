// Keycodes to use jis keycode in us keymap

#pragma once

#include "action.h"
#include "quantum_keycodes.h"
#include "bmp_custom_keycode.h"

enum jtu_custom_keycodes {
  JU_2 = BMP_SAFE_RANGE,
  JU_6,
  JU_7,
  JU_8,
  JU_9,
  JU_0,
  JU_MINS,
  JU_EQL,
  JU_LBRC,
  JU_RBRC,
  JU_BSLS,
  JU_SCLN,
  JU_QUOT,
  JU_GRV,
  JU_CAPS,
  JTU_SAFE_RANGE
};

#define JTU_START_KC JU_2
#define JTU_END_KC JU_CAPS
#define JTU_KEY_STRINGS "JU_2\0JU_6\0JU_7\0JU_8\0JU_9\0JU_0\0JU_MINS\0JU_EQL\0JU_LBRC\0JU_RBRC\0JU_BSLS\0JU_SCLN\0JU_QUOT\0JU_GRV\0JU_CAPS\0"

bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record);
