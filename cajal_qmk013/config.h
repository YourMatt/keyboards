/* Copyright 2020 Worldspawn <mcmancuso@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5742 // WB
#define PRODUCT_ID      0x6361 // CJ
#define DEVICE_VER      0x0001
#define MANUFACTURER    Walletburner
#define PRODUCT         Cajal

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { D4, D5, C7, C6 }
#define MATRIX_COL_PINS { F4, F1, F0, E6, B0, B1, B2, B3, D0, D1, D2, D3, B4, F6 }
#define UNUSED_PINS

#define ENCODERS_PAD_A { D6 }
#define ENCODERS_PAD_B { D7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set value if keys start to chatter. Was originally set to 5. */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* RGB options */
#define RGB_DI_PIN F7
#ifdef RGB_DI_PIN

    #define RGBLIGHT_CAJAL // dims leds in front of arrow keys to account for the closer edge positions of the leds
    #define RGBLED_NUM 18
    #define RGBLIGHT_HUE_STEP 2
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8

    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
    #define RGBLIGHT_LAYER_BLINK
    #define RGBLIGHT_SLEEP

#endif

// may need following for setting macro record to also stop recording, but removed when running example code caused an error
//#define DYNAMIC_MACRO_USER_CALL

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE // use Windows unicode handler

#define COMBO_COUNT 19
#define COMBO_TERM 50
