/***********************************************************************************************************************
*
*   YOURMATT: Cajal Mapping
*
***********************************************************************************************************************/

#include QMK_KEYBOARD_H

/* TODO:
    - Keymap
        - Change RGB mode controls
    - Macros
        - Move to be under shift on layer 2 if tap - Keep shift if held
        - Set record tap to stop record if already recording
    - Underglow
        - Set glow state for right-shift - Not working likely due to use MT with mod_rsft - Explanation is that
          process_record_user is not called for mod-tap and instead uses register_code directly - May not be able to fix
          this issue
        - Add custom animation for RGB_TOG that dims LEDs under the arrows by 50%
    - Layers
        - Consider application-specific shortcuts
        - Add pre-recorded macros for layer 3 under right hand
    - Encoder
        - Decide what to do with it
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
    GI_MACRO1, GI_MACRO2, GI_FN1, GI_FN2, GI_CAPS, GI_SHIFT, GI_CTL, GI_RESET
};
enum unicode_names {
    U_ARROW_CCW, U_ARROW_CW, U_ARROW_DOWN, U_ARROW_LEFT, U_ARROW_RIGHT, U_ARROW_UP,
    U_BULLET, U_CENTS, U_COPY, U_DEGREE, U_DIVIDE, U_ELLIPSIS, U_INTERROBANG, U_MICRO, U_PLUSMINUS, U_REG, U_SKULL,
    U_STAR_FILLED, U_STAR_OUTLINE, U_TIMES, U_TRIANGLE_DOWN, U_TRIANGLE_LEFT, U_TRIANGLE_RIGHT, U_TRIANGLE_UP,
    U_E_EYEROLL, U_E_JOY, U_E_KISS, U_E_LOVE, U_E_ROFL, U_E_SMILE, U_E_THINK
};



/***********************************************************************************************************************
*
*   UNICODE CHARACTERS
*   These will only be usable if the Windows utility is also installed. Install from:
*   https://github.com/samhocevar/wincompose/releases
*
***********************************************************************************************************************/

/*  Remaining layer-3 characters:
    e g h i j k l n o s t u v w y z ,
    That includes top row Y-P and 2nd row G-L. Might block off this section for macros. If so that, leaves the
    following for characters:
    e n s v z ,
*/

const uint32_t PROGMEM unicode_map[] = {

    // unicode
    [U_ARROW_CCW] = 0x21BA,         // ↺	try for combo up/left - just as use case to see if doable - will probably never actually use this
    [U_ARROW_CW] = 0x21BB,          // ↻	try for combo up/right - the trick is using a combo on a single-shot layer
    [U_ARROW_DOWN] = 0x2193,        // ↓	down arrow
    [U_ARROW_LEFT] = 0x2190,        // ←	left arrow
    [U_ARROW_RIGHT] = 0x2192,       // →	right arrow
    [U_ARROW_UP] = 0x2191,          // ↑	up arrow
    [U_BULLET]  = 0x2022,           // •	b
    [U_CENTS] = 0x00A2,             // ¢	f
    [U_COPY]    = 0x00A9,           // ©	c
    [U_DEGREE]  = 0x00B0,           // °	d
    [U_DIVIDE]  = 0x00F7,           // ÷	p
    [U_ELLIPSIS]    = 0x2026,       // …	.
    [U_INTERROBANG] = 0x203D,       // ‽	a
    [U_MICRO] = 0x00B5,             // µ	m
    [U_PLUSMINUS] = 0x00B1,         // ±	]
    [U_REG] = 0x00AE,               // ®	r
    [U_SKULL] = 0x2620,             // ☠	esc
    [U_STAR_FILLED] = 0x2605,       // ★	q
    [U_STAR_OUTLINE] = 0x2606,      // ☆	w
    [U_TIMES] = 0x00D7,             // ×	x
    [U_TRIANGLE_DOWN] = 0x23F7,     // ⏷	rshift
    [U_TRIANGLE_LEFT] = 0x23F4,     // ⏴	;
    [U_TRIANGLE_RIGHT] = 0x23F5,    // ⏵	enter
    [U_TRIANGLE_UP] = 0x23F6,       // ⏶	[

    // emojis
    [U_E_EYEROLL] = 0x1F644,        // 🙄	ctrl
    [U_E_JOY] = 0x1F602,            // 😂	backspace
    [U_E_KISS] = 0x1F618,           // 😘	lalt
    [U_E_LOVE] = 0x1F60D,           // 😍	menu
    [U_E_ROFL] = 0x1F923,           // 🤣	ralt
    [U_E_SMILE] = 0x1F600,          // 😀	space
    [U_E_THINK] = 0x1F914           // 🤔	lshift

};



/***********************************************************************************************************************
*
*   COMBOS
*
***********************************************************************************************************************/

enum combo_events {
    C_FRAC_1_2,
    C_FRAC_1_3,
    C_FRAC_2_3,
    C_FRAC_1_4,
    C_FRAC_3_4,
    C_FRAC_1_5,
    C_FRAC_2_5,
    C_FRAC_3_5,
    C_FRAC_4_5,
    C_FRAC_1_6,
    C_FRAC_5_6,
    C_FRAC_1_7,
    C_FRAC_1_8,
    C_FRAC_3_8,
    C_FRAC_5_8,
    C_FRAC_7_8,
    C_FRAC_1_9,
    C_FRAC_1_10,
    C_FRAC_0_3
};

const uint16_t PROGMEM combo_frac_1_2[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM combo_frac_1_3[] = {KC_1, KC_3, COMBO_END};
const uint16_t PROGMEM combo_frac_2_3[] = {KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM combo_frac_1_4[] = {KC_1, KC_4, COMBO_END};
const uint16_t PROGMEM combo_frac_3_4[] = {KC_3, KC_4, COMBO_END};
const uint16_t PROGMEM combo_frac_1_5[] = {KC_1, KC_5, COMBO_END};
const uint16_t PROGMEM combo_frac_2_5[] = {KC_2, KC_5, COMBO_END};
const uint16_t PROGMEM combo_frac_3_5[] = {KC_3, KC_5, COMBO_END};
const uint16_t PROGMEM combo_frac_4_5[] = {KC_4, KC_5, COMBO_END};
const uint16_t PROGMEM combo_frac_1_6[] = {KC_1, KC_6, COMBO_END};
const uint16_t PROGMEM combo_frac_5_6[] = {KC_5, KC_6, COMBO_END};
const uint16_t PROGMEM combo_frac_1_7[] = {KC_1, KC_7, COMBO_END};
const uint16_t PROGMEM combo_frac_1_8[] = {KC_1, KC_8, COMBO_END};
const uint16_t PROGMEM combo_frac_3_8[] = {KC_3, KC_8, COMBO_END};
const uint16_t PROGMEM combo_frac_5_8[] = {KC_5, KC_8, COMBO_END};
const uint16_t PROGMEM combo_frac_7_8[] = {KC_7, KC_8, COMBO_END};
const uint16_t PROGMEM combo_frac_1_9[] = {KC_1, KC_9, COMBO_END};
const uint16_t PROGMEM combo_frac_1_10[] = {KC_1, KC_0, COMBO_END};
const uint16_t PROGMEM combo_frac_0_3[] = {KC_0, KC_3, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [C_FRAC_1_2] = COMBO_ACTION(combo_frac_1_2),
    [C_FRAC_1_3] = COMBO_ACTION(combo_frac_1_3),
    [C_FRAC_2_3] = COMBO_ACTION(combo_frac_2_3),
    [C_FRAC_1_4] = COMBO_ACTION(combo_frac_1_4),
    [C_FRAC_3_4] = COMBO_ACTION(combo_frac_3_4),
    [C_FRAC_1_5] = COMBO_ACTION(combo_frac_1_5),
    [C_FRAC_2_5] = COMBO_ACTION(combo_frac_2_5),
    [C_FRAC_3_5] = COMBO_ACTION(combo_frac_3_5),
    [C_FRAC_4_5] = COMBO_ACTION(combo_frac_4_5),
    [C_FRAC_1_6] = COMBO_ACTION(combo_frac_1_6),
    [C_FRAC_5_6] = COMBO_ACTION(combo_frac_5_6),
    [C_FRAC_1_7] = COMBO_ACTION(combo_frac_1_7),
    [C_FRAC_1_8] = COMBO_ACTION(combo_frac_1_8),
    [C_FRAC_3_8] = COMBO_ACTION(combo_frac_3_8),
    [C_FRAC_5_8] = COMBO_ACTION(combo_frac_5_8),
    [C_FRAC_7_8] = COMBO_ACTION(combo_frac_7_8),
    [C_FRAC_1_9] = COMBO_ACTION(combo_frac_1_9),
    [C_FRAC_1_10] = COMBO_ACTION(combo_frac_1_10),
    [C_FRAC_0_3] = COMBO_ACTION(combo_frac_0_3)
};

void process_combo_event(uint16_t combo_index, bool pressed) {

    if (!pressed) return;

    switch (combo_index) {
        case C_FRAC_1_2:
            send_unicode_string("½");
            break;
        case C_FRAC_1_3:
            send_unicode_string("⅓");
            break;
        case C_FRAC_2_3:
            send_unicode_string("⅔");
            break;
        case C_FRAC_1_4:
            send_unicode_string("¼");
            break;
        case C_FRAC_3_4:
            send_unicode_string("¾");
            break;
        case C_FRAC_1_5:
            send_unicode_string("⅕");
            break;
        case C_FRAC_2_5:
            send_unicode_string("⅖");
            break;
        case C_FRAC_3_5:
            send_unicode_string("⅗");
            break;
        case C_FRAC_4_5:
            send_unicode_string("⅘");
            break;
        case C_FRAC_1_6:
            send_unicode_string("⅙");
            break;
        case C_FRAC_5_6:
            send_unicode_string("⅚");
            break;
        case C_FRAC_1_7:
            send_unicode_string("⅐");
            break;
        case C_FRAC_1_8:
            send_unicode_string("⅛");
            break;
        case C_FRAC_3_8:
            send_unicode_string("⅜");
            break;
        case C_FRAC_5_8:
            send_unicode_string("⅝");
            break;
        case C_FRAC_7_8:
            send_unicode_string("⅞");
            break;
        case C_FRAC_1_9:
            send_unicode_string("⅑");
            break;
        case C_FRAC_1_10:
            send_unicode_string("⅒");
            break;
        case C_FRAC_0_3:
            send_unicode_string("↉");
            break;
    }

}



/***********************************************************************************************************************
*
*   KEYMAP
*
***********************************************************************************************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [L_DEFAULT] = LAYOUT_stagger(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, RGB_TOG,
        KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLASH), KC_UP,
        MO(L_1), KC_LALT, KC_LGUI, KC_BSPACE, KC_SPC, KC_RALT, MO(L_2), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [L_1] = LAYOUT_stagger(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, RGB_MOD,
        KC_TRNS, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_QUOTE, KC_TRNS,
        KC_TRNS, DYN_REC_START1, DYN_REC_START2, DYN_REC_STOP, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_BSLASH, KC_PGUP,
        KC_TRNS, KC_TRNS, /*LT(L_4, KC_HOME),*/ KC_TRNS, KC_INSERT, KC_TAB, KC_0, OSL(L_3), KC_HOME, KC_PGDN, KC_END
    ),

    [L_2] = LAYOUT_stagger(
        KC_CAPSLOCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
        KC_TRNS, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_TRNS, KC_TRNS, RGB_SAD, RGB_SAI, KC_TRNS, RGB_VAI,
        OSL(L_3), KC_TRNS, KC_TRNS, KC_DELETE, KC_TRNS, KC_END, KC_TRNS, RGB_HUD, RGB_VAD, RGB_HUI
    ),

    [L_3] = LAYOUT_stagger(
        X(U_SKULL), X(U_STAR_FILLED), X(U_STAR_OUTLINE), KC_TRNS, X(U_REG), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, X(U_DIVIDE), X(U_TRIANGLE_UP), X(U_PLUSMINUS), RESET,
        X(U_E_EYEROLL), X(U_INTERROBANG), KC_TRNS, X(U_DEGREE), X(U_CENTS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, X(U_TRIANGLE_LEFT), X(U_TRIANGLE_RIGHT),
        X(U_E_THINK), KC_TRNS, X(U_TIMES), X(U_COPY), KC_TRNS, X(U_BULLET), KC_TRNS, X(U_MICRO), KC_TRNS, X(U_ELLIPSIS), X(U_TRIANGLE_DOWN), X(U_ARROW_UP),
        KC_TRNS, X(U_E_KISS), X(U_E_LOVE), X(U_E_JOY), X(U_E_SMILE), X(U_E_ROFL), KC_TRNS, X(U_ARROW_LEFT), X(U_ARROW_DOWN), X(U_ARROW_RIGHT)
    )

};



/***********************************************************************************************************************
*
*   LAYER STATE CHANGE HOOK
*
***********************************************************************************************************************/

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {

        case L_1:
            writePinHigh(B7);
            writePinLow(B6);
            rgblight_set_layer_state(GI_FN1, 1);
            break;

        case L_2:
            writePinLow(B7);
            writePinHigh(B6);
            rgblight_set_layer_state(GI_FN2, 1);
            break;

        case L_3:
            writePinHigh(B7);
            writePinHigh(B6);
            rgblight_set_layer_state(GI_FN1, 1);
            rgblight_set_layer_state(GI_FN2, 1);
            break;

        default:
            writePinLow(B7);
            writePinLow(B6);
            rgblight_set_layer_state(GI_FN1, 0);
            rgblight_set_layer_state(GI_FN2, 0);
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

    //writePin(B5, led_state.caps_lock);
    rgblight_set_layer_state(GI_CAPS, led_state.caps_lock);

    return false;

}



/***********************************************************************************************************************
*
*   ROTARY ENCODER HOOK
*
***********************************************************************************************************************/

// TEMPORARILY UPDATED TO CYCLE THROUGH LEDS WHILE TESTING LIGHT ISOLATION ON PHYSICAL BOARD
static uint16_t ENC_TRACKER = 0;
void encoder_update_user(uint8_t index, bool clockwise) {

    if (clockwise) ENC_TRACKER++;
    else ENC_TRACKER--;

    switch (ENC_TRACKER % 4) {
        case 0:
            writePinLow(B5);
            writePinLow(B6);
            writePinLow(B7);
            break;
        case 1:
            writePinHigh(B5);
            writePinLow(B6);
            writePinLow(B7);
            break;
        case 2:
            writePinLow(B5);
            writePinHigh(B6);
            writePinLow(B7);
            break;
        case 3:
            writePinLow(B5);
            writePinLow(B6);
            writePinHigh(B7);
            break;
    }

/*
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        }
        else {
            tap_code(KC_VOLU);
        }
    }
*/

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
    glow_macro_rec_1, glow_macro_rec_2, glow_layer_fn1, glow_layer_fn2, glow_caps, glow_shift, glow_ctl, glow_reset
);



/***********************************************************************************************************************
*
*   KEYPRESS EVENTS
*
***********************************************************************************************************************/

static bool H_SHIFT = false;
static bool H_L1_ALT = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    /* // FAILED WITH:  error: implicit declaration of function ‘process_record_dynamic_macro’ [-Werror=implicit-function-declaration]
        uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);
        if (!process_record_dynamic_macro(macro_kc, record)) {
            return false;
        }
    */

    // blink example - use while recording macros
    //rgblight_blink_layer(2, 500); // this doesn't go on and off - just stays on for duration

    uint8_t layer = biton32(layer_state);
    switch (keycode) {
        case KC_LSFT:
            H_SHIFT = record->event.pressed;
            rgblight_set_layer_state(GI_SHIFT, record->event.pressed);
            return true;
        case KC_RSFT: // currently not operational
            rgblight_set_layer_state(GI_SHIFT, record->event.pressed);
            return true;
        case KC_LALT:
        case KC_RALT:
            if (!record->event.pressed) H_L1_ALT = false; // reset alt if layer 1 released before alt
            if (layer == L_1) {
                H_L1_ALT = record->event.pressed;
                return false;
            }
            return true;
        case KC_LCTRL:
            rgblight_set_layer_state(GI_CTL, record->event.pressed);
            return true;
        case DYN_REC_START1:
            rgblight_set_layer_state(GI_MACRO1, 1);
            return true;
        case DYN_REC_START2:
            rgblight_set_layer_state(GI_MACRO2, 1);
            return true;
        case DYN_REC_STOP:
            rgblight_set_layer_state(GI_MACRO1, 0);
            rgblight_set_layer_state(GI_MACRO1, 0);
            return true;

        // set super and subscript for all numbers
        case KC_1:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("¹"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₁"); return false; }
            }
            return true;
        case KC_2:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("²"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₂"); return false; }
            }
            return true;
        case KC_3:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("³"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₃"); return false; }
            }
            return true;
        case KC_4:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁴"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₄"); return false; }
            }
            return true;
        case KC_5:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁵"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₅"); return false; }
            }
            return true;
        case KC_6:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁶"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₆"); return false; }
            }
            return true;
        case KC_7:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁷"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₇"); return false; }
            }
            return true;
        case KC_8:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁸"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₈"); return false; }
            }
            return true;
        case KC_9:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁹"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₉"); return false; }
            }
            return true;
        case KC_0:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁰"); return false; }
                else if (H_L1_ALT) { send_unicode_string("₀"); return false; }
            }
            return true;
        case KC_BSLASH:
            if (record->event.pressed && H_L1_ALT) { send_unicode_string("⁄"); return false; }
            return true;

        // dfu
        case RESET:

            // turn off all layer lights
            rgblight_set_layer_state(GI_FN1, 0);
            rgblight_set_layer_state(GI_FN2, 0);

            // turn on the reset light
            rgblight_set_layer_state(GI_RESET, 1);

            return true;

        default:
            return true;

    }
}



/*
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    // INSERT CODE HERE: turn off all leds

    switch (layer) {
        case L_1:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_1
            break;
        case L_2:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
            break;
        // add case for each layer
    }
};
*/



/***********************************************************************************************************************
*
*   KEYBOARD READY STATE
*
***********************************************************************************************************************/

void keyboard_post_init_user(void) {

    rgblight_layers = glow_layers;
    rgblight_set_layer_state(GI_FN1, 0); // refresh glow state - was turning on green lights on right edge when coming out of DFU

}
