/*
 * YourMatt: Cajal Mapping
 */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_stagger(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, RGB_TOG,
        KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLASH), KC_UP,
        MO(1), KC_LALT, KC_LGUI, KC_BSPACE, KC_SPC, KC_RALT, MO(2), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_stagger(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, RGB_MOD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_QUOTE, KC_TRNS,
        KC_TRNS, DYN_REC_START1, DYN_REC_START2, DYN_REC_STOP, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_BSLASH, KC_PGUP,
        KC_TRNS, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, KC_INSERT, KC_TAB,  KC_0, MO(3),  KC_HOME, KC_PGDN, KC_END
    ),
    [2] = LAYOUT_stagger(
        KC_CAPSLOCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
        KC_TRNS, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_TRNS, KC_TRNS, RGB_SAD, RGB_SAI, KC_TRNS, RGB_VAI,
        MO(3), KC_TRNS, KC_TRNS, KC_DELETE, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUD, RGB_VAD, RGB_HUI
    ),
    [3] = LAYOUT_stagger(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 1:
        writePinHigh(B7);
        writePinLow(B6);

    	rgblight_set_layer_state(4, 1);
        break;
    case 2:
        writePinLow(B7);
        writePinHigh(B6);
        break;
    case 3:
        writePinHigh(B7);
        writePinHigh(B6);
        break;
    default:
        writePinLow(B7);
        writePinLow(B6);
    	rgblight_set_layer_state(4, 0);
        break;
    }
    return state;
}

bool led_update_user(led_t led_state) {
    writePin(B5, led_state.caps_lock);

    rgblight_set_layer_state(0, led_state.caps_lock);

    //rgblight_sethsv_at(128, 128, 128, 4);

    return false;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
}



// RGB LED Indicators
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, 0, 255, 128},
    {10, 1, 0, 255, 255},
    {11, 1, 0, 255, 128}
);
const rgblight_segment_t PROGMEM my_test_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, 24, 255, 255},
    {4, 1, 24, 255, 255}
);
const rgblight_segment_t PROGMEM my_reset_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 5, 0, 255, 255}
);
const rgblight_segment_t PROGMEM layer_lalt[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, 24, 255, 255}
);
const rgblight_segment_t PROGMEM layer_fn1[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, 24, 255, 255}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_test_layer,
    my_reset_layer,
    layer_lalt,
    layer_fn1
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_RALT:
        rgblight_set_layer_state(1, record->event.pressed);
      	return true;
    case KC_LALT:
        rgblight_set_layer_state(3, record->event.pressed);
      	return true;
    case RESET:
        rgblight_set_layer_state(2, 1);
      	return true;
        //rgblight_blink_layer(2, 500); // this doesn't go on and off - just stays on for duration
    default:
      return true; // Process all other keycodes normally
  }
}
