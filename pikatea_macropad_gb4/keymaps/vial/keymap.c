/* Copyright 2020 Jack Kester
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
#include QMK_KEYBOARD_H
#include "rgb_profiles.h"

#define LAYOUT_via( \
    k00, k01, k02, k03, k04, k05, k06, k07,  \
    E00A, E00B \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { E00A,  E00B } \
}

// use the names from vial.json
enum blender_keycode {
    RGB_USER_GREEN = USER00,
    RGB_USER_RED, 
    RGB_USER_BLUE,
    RGB_USER_WHITE,
    RGB_USER_YELLOW,
    RGB_USER_ORANGE,
    RGB_USER_CYAN,
    RGB_USER_PURPLE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_via(
        KC_F13,   KC_F14,  KC_F15,  KC_F16,   KC_MEDIA_PREV_TRACK,    KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,    KC_MUTE,
        KC_VOLU, KC_VOLD
    ),
    [1] = LAYOUT_via(
        _______,   _______,   _______,   _______,   _______,    _______,    _______,    _______,
        _______,   _______
    ),
    [2] = LAYOUT_via(
        _______,   _______,   _______,   _______,   _______,    _______,    _______,    _______,
        _______,   _______
    )
};

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = default_rgb_layers;
}

void update_rgb_layer(uint8_t layer_code) {
    // basic limit checking
    if (layer_code >= NUMBER_OF_RGB_LAYERS) {
        return;
    }

    // higher rgblight layers take precedence, so disable them
    for (int i=layer_code+1; i < NUMBER_OF_RGB_LAYERS; i++) {
        rgblight_set_layer_state(i, false);
    }

    // enable the desired rgblight layer
    rgblight_set_layer_state(layer_code, true);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case RGB_USER_GREEN:
            if (record->event.pressed) { 
                update_rgb_layer(0);
                return 0;
            }
        case RGB_USER_RED:
            if (record->event.pressed) {
                update_rgb_layer(1);
                return 0;
            }
        case RGB_USER_BLUE:
            if (record->event.pressed) {
                update_rgb_layer(2);
                return 0;
            }
        case RGB_USER_WHITE:
            if (record->event.pressed) { 
                update_rgb_layer(3);
                return 0;
            }
        case RGB_USER_YELLOW:
            if (record->event.pressed) {
                update_rgb_layer(4);
                return 0;
            }
        case RGB_USER_ORANGE:
            if (record->event.pressed) {
                update_rgb_layer(5);
                return 0;
            }
        case RGB_USER_CYAN:
            if (record->event.pressed) {
                update_rgb_layer(6);
                return 0;
            }
        case RGB_USER_PURPLE:
            if (record->event.pressed) {
                update_rgb_layer(7);
                return 0;
            }
        default:
            return true;
    }
    return true;
}