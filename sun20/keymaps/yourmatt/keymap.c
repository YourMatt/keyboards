/***********************************************************************************************************************
*
*   YOURMATT: Sun20Pro Mapping
*
***********************************************************************************************************************/

#include "sun20p.h"

/* TODO:
    - Keymap
      - Set application-specific layers
    - Underglow
      - Turn off by default
      - Switch lights by layer

*/

/***********************************************************************************************************************
*
*   CONSTANTS
*
***********************************************************************************************************************/

enum layer_indexes {
    L_DEFAULT, L_1, L_2, L_3
};
enum glow_indexes {
    GI_DEFAULT, GI_LAYER1, GI_LAYER2, GI_RESET
};


/***********************************************************************************************************************
*
*   KEYMAP
*
***********************************************************************************************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_ESCAPE, KC_SLASH, KC_ASTERISK, KC_MINUS,
		KC_7, KC_8, KC_9,
		KC_4, KC_5, KC_6, KC_PLUS,
		KC_1, KC_2, KC_3, RESET, /*KC_MUTE,*/
		KC_0, KC_DOT, KC_ENTER),

	KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

};


/***********************************************************************************************************************
*
*   UNDERGLOW
*   Can define a max of 8 underglow layers
*
*   Layout:
*
*   4   8   13  16
*   3   7   12  15      24
*   2   6   11          |
*   1   5   10  14      |
*   0       9           17
*
***********************************************************************************************************************/

// default
const rgblight_segment_t PROGMEM glow_default[] = RGBLIGHT_LAYER_SEGMENTS(
	{20, 1, 0, 255, 255}
);
// layer 1
const rgblight_segment_t PROGMEM glow_layer1[] = RGBLIGHT_LAYER_SEGMENTS(
	{21, 1, 25, 255, 255}
);
// layer 2
const rgblight_segment_t PROGMEM glow_layer2[] = RGBLIGHT_LAYER_SEGMENTS(
	{22, 1, 50, 255, 255}
);
// dfu
const rgblight_segment_t PROGMEM glow_reset[] = RGBLIGHT_LAYER_SEGMENTS(
    {17, 8, 0, 255, 255}
);

const rgblight_segment_t* const PROGMEM glow_layers[] = RGBLIGHT_LAYERS_LIST(
    glow_default, glow_layer1, glow_layer2, glow_reset
);

/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}
*/

static uint8_t ENC_TRACKER = 0;
void encoder_update_user(uint8_t index, bool clockwise) {

    rgblight_set_layer_state(GI_DEFAULT, 0);
    rgblight_set_layer_state(GI_LAYER1, 0);
    rgblight_set_layer_state(GI_LAYER2, 0);
    rgblight_set_layer_state(GI_RESET, 0);

    if (clockwise) ENC_TRACKER--;
    else ENC_TRACKER++;

    switch (ENC_TRACKER % 4) {
        case 0:
            rgblight_set_layer_state(GI_DEFAULT, 1);
            break;
        case 1:
            rgblight_set_layer_state(GI_LAYER1, 1);
            break;
        case 2:
            rgblight_set_layer_state(GI_LAYER2, 1);
            break;
        case 3:
            rgblight_set_layer_state(GI_RESET, 1);
            break;
    }

    /*
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    */

}

/*
void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
*/


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // blink example - use while recording macros
    //rgblight_blink_layer(2, 500); // this doesn't go on and off - just stays on for duration

    //uint8_t layer = biton32(layer_state);
    switch (keycode) {

        // dfu
        case RESET:

            // turn off all layer lights
            //rgblight_set_layer_state(GI_FN1, 0);
            //rgblight_set_layer_state(GI_FN2, 0);

            // turn on the reset light
            rgblight_set_layer_state(GI_RESET, 1);

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

    rgblight_disable();

    rgblight_layers = glow_layers;
    rgblight_set_layer_state(GI_DEFAULT, 0); // refresh glow state - was turning on green lights on right edge when coming out of DFU

}
