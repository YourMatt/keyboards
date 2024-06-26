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
      - Lightroom - Use #31A8FF for LED color (matching Adobe app icon color)
        g - Switch to Library Grid
        e - Switch to Library Loupe
        d - Switch to Develop
        r - Switch to Develop with Crop Overlay
        f - Full screen photo
        l - Lights-out modes
        n - Survey mode to show selected photos and narrow down to keepers
        b - Add to target collection - Need to right-click collection folder first and then mark for target collection
        y - Before/after view
        0-5 - Set rating (shift+# will set rating then move to next)
        Ctrl+Enter - Slideshow of all images starting at selection
        , - Go up in adjustment list
        . - Go down in adjustment list
        + - Raise value for selected adjustment
        - - Lower value for selected adjustment
        Ctrl+Shift+C - Copy develop settings
        Ctrl+Shift+V - Paste develop settings
    - Underglow
      x Turn off by default
      x Switch lights by layer

        OS Standard
		KVM1        KVM2        KVM2        COLOR PKR
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

    // used for 10-key
	[L_DEFAULT] = KEYMAP(
		KC_BSPACE, KC_SLASH, KC_ASTERISK, KC_MINUS,
		KC_7, KC_8, KC_9,
		KC_4, KC_5, KC_6, KC_PLUS,
		KC_1, KC_2, KC_3, RESET,
		KC_0, KC_DOT, KC_ENTER),

    // used for OS-level commands
	[L_1] = KEYMAP(
		CKC_KVM_INPUT_1, CKC_KVM_INPUT_2, CKC_KVM_INPUT_3, SWIN(KC_C),
		LWIN(LCTL(KC_LEFT)), LALT(LCTL(KC_TAB)), LWIN(LCTL(KC_RIGHT)),
		LCTL(KC_C), KC_TRNS, LCTL(KC_V), KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, MT(MOD_LSFT, KC_ENTER)),

    // used for Lightroom
	[L_2] = KEYMAP(
		KC_G, KC_E, KC_D, C(KC_ENTER),              // view switching: grid, loupe, develop, slideshow
		KC_F, KC_L, S(KC_TAB),                      // full screen, lights-out, show/hide panels
		C(S(KC_C)), KC_COMMA, C(S(KC_V)), KC_RBRC,  // copy adjustments, prev adjustment, paste adjustment, rating up
		KC_MINUS, KC_DOT, S(KC_EQUAL), KC_TRNS,     // lower value, next adjustment, raise value, unused
		KC_LEFT, KC_RIGHT, KC_LBRC),                // previous photo, next photo, rating down

	[L_3] = KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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

// OS commands layer
const rgblight_segment_t PROGMEM glow_layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {17, 1, 30, 255, 25},   // yellow
    {18, 1, 30, 255, 75},   // yellow
    {19, 4, 30, 255, 153},  // yellow
    {23, 1, 30, 255, 75},   // yellow
    {24, 1, 30, 255, 25}    // yellow
);
// Lightroom commands layer
const rgblight_segment_t PROGMEM glow_layer3[] = RGBLIGHT_LAYER_SEGMENTS(
	{17, 1, 160, 255, 25},  // blue
	{18, 1, 160, 255, 75},  // blue
	{19, 4, 160, 255, 153}, // blue
	{23, 1, 160, 255, 75},  // blue
	{24, 1, 160, 255, 25}   // blue
);
// dfu
const rgblight_segment_t PROGMEM glow_reset[] = RGBLIGHT_LAYER_SEGMENTS(
    {17, 8, 0, 255, 255}    // red
);

const rgblight_segment_t* const PROGMEM glow_layers[] = RGBLIGHT_LAYERS_LIST(
    glow_layer2, glow_layer3, glow_reset
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
    switch (ENC_TRACKER % 3) {
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

        // disabled - change mod value above to enable
        case 3:
            layer_on(L_3);
            rgblight_set_layer_state(GI_RESET, 1);
            break;
    }

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
