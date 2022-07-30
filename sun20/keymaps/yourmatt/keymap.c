/***********************************************************************************************************************
*
*   YOURMATT: Sun20Pro Mapping
*   qmk compile -kb yourmatt/sun20 -km yourmatt
*   Enter DFU by: Rotate knob until all LEDs off, then press knob
*
***********************************************************************************************************************/

#include "sun20p.h"

/* TODO:
    - Keymap
      - Set application-specific layers
      - Default
        - Standard 10-key setup
      - OS
        - KVM switcher
        - Display all programs on desktop - Ctrl-Alt-Tab
        - Move to virtual desktop ← or →
        - Move to virtual desktop and bring current window ← or →
        - Cut / Copy / Paste
        - Copy History - Win-V
        - Color Picker - Win-Shift-C
        - Decided against:
          - Search - Alt-Space
          - Caps might be nice
      - Excel
        - Numbers/Dot/Enter (leaves 5 remaining, but may want to add a layer as well)
        - Edit cell (F2)
        - Copy
        - Paste
        - Header style (bold + thick bottom border)
        -
    - Underglow
      x Turn off by default
      x Switch lights by layer

        OS Standard
		KVM 1       KVM 2       KVM2        *
		VD LEFT     SHOW WINS   VD RIGHT
		COPY        *           PASTE       ↻
		*           *           *           *
		MACRO START             MCRO STP    MOD

		OS Mod
        *           *           *           *
        VD MOV WIN LEFT         VD MOV WIN RIGHT
        *           *           *           *
        *           *           *           *
        *                       *           *

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
    GI_LAYER1, GI_LAYER2, GI_RESET
};
enum custom_keycodes {
    CKC_CALC = SAFE_RANGE,
    CKC_KVM_INPUT_1, CKC_KVM_INPUT_2, CKC_KVM_INPUT_3
};


/***********************************************************************************************************************
*
*   KEYMAP
*
***********************************************************************************************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[L_DEFAULT] = KEYMAP(
		KC_BSPACE, KC_SLASH, KC_ASTERISK, KC_MINUS,
		KC_7, KC_8, KC_9,
		KC_4, KC_5, KC_6, KC_PLUS,
		KC_1, KC_2, KC_3, RESET,
		KC_0, KC_DOT, KC_ENTER),

	[L_1] = KEYMAP(
		CKC_KVM_INPUT_1, CKC_KVM_INPUT_2, CKC_KVM_INPUT_3, SWIN(KC_C),
		LWIN(LCTL(KC_LEFT)), LALT(LCTL(KC_TAB)), LWIN(LCTL(KC_RIGHT)),
		LCTL(KC_C), LCTL(KC_V), KC_LSFT, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, MT(MOD_LSFT, KC_ENTER)),

	[L_2] = KEYMAP(
		KC_CALC, KC_WWW_BACK, KC_WWW_FORWARD, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_SYSTEM_SLEEP, KC_SYSTEM_WAKE, KC_TRNS),

	[L_3] = KEYMAP(
		KC_C, KC_C, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS)

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

// calculator
const rgblight_segment_t PROGMEM glow_layer1[] = RGBLIGHT_LAYER_SEGMENTS(
	{17, 2, 43, 255, 220}, // yellow
	{19, 2, 160, 255, 200}, // blue
	{21, 2, 85, 255, 220}, // green
	{23, 2, 0, 255, 160} // red
);
// layer 2
const rgblight_segment_t PROGMEM glow_layer2[] = RGBLIGHT_LAYER_SEGMENTS(
	{17, 8, 25, 255, 128}
);
// dfu
const rgblight_segment_t PROGMEM glow_reset[] = RGBLIGHT_LAYER_SEGMENTS(
    {17, 8, 0, 255, 255}
);

const rgblight_segment_t* const PROGMEM glow_layers[] = RGBLIGHT_LAYERS_LIST(
    glow_layer1, glow_layer2, glow_reset
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

    rgblight_set_layer_state(GI_LAYER1, 0);
    rgblight_set_layer_state(GI_LAYER2, 0);
    rgblight_set_layer_state(GI_RESET, 0);

    if (clockwise) ENC_TRACKER++;
    else ENC_TRACKER--;

    layer_clear();
    switch (ENC_TRACKER % 4) {
        case 0:
            layer_on(L_DEFAULT);
            break;
        case 1:
            layer_on(L_1);
            rgblight_set_layer_state(GI_LAYER1, 1);
            break;
        case 2:
            layer_on(L_2);
            rgblight_set_layer_state(GI_LAYER2, 1);
            break;
        case 3:
            layer_on(L_3);
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

        //
        case KC_COPY:
            if (record->event.pressed) {
                /*
                if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) {
                    register_code(KC_0);
                }
                else {
                    register_code(KC_1);
                }
                */
            }
            return false;
        case KC_PASTE:

            return false;

        // kvm switchers
        case CKC_KVM_INPUT_1:
            if (record->event.pressed) {
                tap_code_delay(KC_SCROLLLOCK, 300);
                tap_code_delay(KC_SCROLLLOCK, 300);
                tap_code(KC_1);
            }
            return false;
        case CKC_KVM_INPUT_2:
            if (record->event.pressed) {
                tap_code_delay(KC_SCROLLLOCK, 300);
                tap_code_delay(KC_SCROLLLOCK, 300);
                tap_code(KC_2);
            }
            return false;
        case CKC_KVM_INPUT_3:
            if (record->event.pressed) {
                tap_code_delay(KC_SCROLLLOCK, 300);
                tap_code_delay(KC_SCROLLLOCK, 300);
                tap_code(KC_3);
            }
            return false;

        // calculator - WIN-R + calc + enter
        case CKC_CALC:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") "calc" SS_TAP(X_ENTER));
            }
            return false;

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
    // rgblight_set_layer_state(GI_LAYER1, 0); // refresh glow state - was turning on green lights on right edge when coming out of DFU

}
