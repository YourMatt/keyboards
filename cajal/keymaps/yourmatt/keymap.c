/***********************************************************************************************************************
*
*   YOURMATT: Cajal Mapping
*
***********************************************************************************************************************/

#include QMK_KEYBOARD_H

/* TODO:
    - Keymap
        - Move DFU Reset
        - Change RGB mode controls
    - Macros
        - Move to be under shift on layer 2 if tap - Keep shift if held
        - Set record tap to stop record if already recording
    - Underglow
        - Set glow state for right-shift - Not working likely due to use MT with mod_rsft
        - Add custom animation for RGB_TOG that dims LEDs under the arrows by 50%
    - Layers
        - Add a new layer that locks on a double-tap of Fn1 - Use this for special characters
        - Consider application-specific shortcuts
            - Excel
                - Edit cell contents
    - Encoder
        - Decide what to do with it
*/


/***********************************************************************************************************************
*
*   KEYMAP
*
***********************************************************************************************************************/

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



/***********************************************************************************************************************
*
*   CONSTANTS
*
***********************************************************************************************************************/

const uint16_t PROGMEM GLOW_INDEX_MACRO1 = 0;
const uint16_t PROGMEM GLOW_INDEX_MACRO2 = 1;
const uint16_t PROGMEM GLOW_INDEX_FN1 = 2;
const uint16_t PROGMEM GLOW_INDEX_FN2 = 3;
const uint16_t PROGMEM GLOW_INDEX_CAPS = 4;
const uint16_t PROGMEM GLOW_INDEX_SHIFT = 5;
const uint16_t PROGMEM GLOW_INDEX_CTL = 6;
const uint16_t PROGMEM GLOW_INDEX_RESET = 7;



/***********************************************************************************************************************
*
*   LAYER STATE CHANGE HOOK
*
***********************************************************************************************************************/

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {

        case 1:
            writePinHigh(B7);
            writePinLow(B6);
            rgblight_set_layer_state(GLOW_INDEX_FN1, 1);
            break;

        case 2:
            writePinLow(B7);
            writePinHigh(B6);
            rgblight_set_layer_state(GLOW_INDEX_FN2, 1);
            break;

        case 3:
            writePinHigh(B7);
            writePinHigh(B6);
            rgblight_set_layer_state(GLOW_INDEX_FN1, 1);
            rgblight_set_layer_state(GLOW_INDEX_FN2, 1);
            break;

        default:
            writePinLow(B7);
            writePinLow(B6);
            rgblight_set_layer_state(GLOW_INDEX_FN1, 0);
            rgblight_set_layer_state(GLOW_INDEX_FN2, 0);
            break;

    }

    return state;

}



/***********************************************************************************************************************
*
*   LED STATE CHANGE HOOK
*
***********************************************************************************************************************/

bool led_update_user(led_t led_state) {

    writePin(B5, led_state.caps_lock);
    rgblight_set_layer_state(GLOW_INDEX_CAPS, led_state.caps_lock);

    return false;

}



/***********************************************************************************************************************
*
*   ROTARY ENCODER HOOK
*
***********************************************************************************************************************/

void encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        }
        else {
            tap_code(KC_VOLU);
        }
    }

}



/***********************************************************************************************************************
*
*   UNDERGLOW
*   Can define a max of 8 underglow layers
*
***********************************************************************************************************************/

// caps lock
const rgblight_segment_t PROGMEM glow_caps[] = RGBLIGHT_LAYER_SEGMENTS(
	{2, 1, 127, 255, 128}, // dimmed light 2 because closer to edge of housing
    {3, 5, 127, 255, 255}
);
// shift
const rgblight_segment_t PROGMEM glow_shift[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, 169, 255, 255},
    {6, 1, 148, 255, 255}
);
// control
const rgblight_segment_t PROGMEM glow_ctl[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, 64, 255, 255},
    {6, 1, 95, 255, 255}
);
// function 1 layer
const rgblight_segment_t PROGMEM glow_layer_fn1[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, 190, 255, 255}
);
//function 2 layer
const rgblight_segment_t PROGMEM glow_layer_fn2[] = RGBLIGHT_LAYER_SEGMENTS(
    {17, 1, 190, 255, 255},
    {0, 1, 190, 255, 255},
    {1, 1, 190, 255, 128} // dimmed light 1 because closer to edge of housing
);
// macro 1 recording
const rgblight_segment_t PROGMEM glow_macro_rec_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, 0, 255, 255}
);
// macro 2 recording
const rgblight_segment_t PROGMEM glow_macro_rec_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, 56, 255, 255}
);
// DFU mode
const rgblight_segment_t PROGMEM glow_reset[] = RGBLIGHT_LAYER_SEGMENTS(
	{2, 1, 0, 255, 128}, // dimmed light 2 because closer to edge of housing
    {3, 5, 0, 255, 255}
);

const rgblight_segment_t* const PROGMEM glow_layers[] = RGBLIGHT_LAYERS_LIST(
    glow_macro_rec_1,
    glow_macro_rec_2,
    glow_layer_fn1,
    glow_layer_fn2,
    glow_caps,
    glow_shift,
    glow_ctl,
    glow_reset
);



/***********************************************************************************************************************
*
*   KEYPRESS EVENTS
*
***********************************************************************************************************************/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    /* // FAILED WITH:  error: implicit declaration of function ‘process_record_dynamic_macro’ [-Werror=implicit-function-declaration]
        uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);
        if (!process_record_dynamic_macro(macro_kc, record)) {
            return false;
        }
    */

    // blink example - use while recording macros
    //rgblight_blink_layer(2, 500); // this doesn't go on and off - just stays on for duration

    switch (keycode) {
        case KC_LSFT:
            rgblight_set_layer_state(GLOW_INDEX_SHIFT, record->event.pressed);
            return true;
        case KC_RSFT:
            rgblight_set_layer_state(GLOW_INDEX_SHIFT, record->event.pressed);
            return true;
        case KC_LCTRL:
            rgblight_set_layer_state(GLOW_INDEX_CTL, record->event.pressed);
            return true;
        case DYN_REC_START1:
            rgblight_set_layer_state(GLOW_INDEX_MACRO1, 1);
            return true;
        case DYN_REC_START2:
            rgblight_set_layer_state(GLOW_INDEX_MACRO2, 1);
            return true;
        case DYN_REC_STOP:
            rgblight_set_layer_state(GLOW_INDEX_MACRO1, 0);
            rgblight_set_layer_state(GLOW_INDEX_MACRO2, 0);
            return true;
        case RESET:

            // turn off all layer lights
            rgblight_set_layer_state(GLOW_INDEX_FN1, 0);
            rgblight_set_layer_state(GLOW_INDEX_FN2, 0);

            // turn on the reset light
            rgblight_set_layer_state(GLOW_INDEX_RESET, 1);

            return true;
        default:
            return true;
    }
}



/***********************************************************************************************************************
*
*   KEYBOARD READY STATE
*
***********************************************************************************************************************/

void keyboard_post_init_user(void) {

    rgblight_layers = glow_layers;
    rgblight_set_layer_state(GLOW_INDEX_FN1, 0); // refresh glow state - was turning on green lights on right edge when coming out of DFU

}
