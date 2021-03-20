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
            - Excel
                - Edit cell contents
    - Encoder
        - Decide what to do with it
*/



/***********************************************************************************************************************
*
*   CONSTANTS
*
***********************************************************************************************************************/

enum layer_indexes {
    L_DEFAULT, L_1, L_2, L_3, L_4
};
enum glow_indexes {
    GI_MACRO1, GI_MACRO2, GI_FN1, GI_FN2, GI_CAPS, GI_SHIFT, GI_CTL, GI_RESET
};
enum unicode_names {
    U_BULLET,
    U_COPY,
    U_DEGREE,
    U_DIVIDE,
    U_ELLIPSIS,
    U_FRAC_1_2, U_FRAC_1_3, U_FRAC_2_3, U_FRAC_1_4, U_FRAC_3_4, U_FRAC_1_8, U_FRAC_3_8, U_FRAC_5_8, U_FRAC_7_8, U_FRAC_SLASH,
    U_INTERROBANG, U_PLUSMINUS /*,
    U_SUB_1, U_SUB_2, U_SUB_3, U_SUB_4, U_SUB_5, U_SUB_6, U_SUB_7, U_SUB_8, U_SUB_9, U_SUB_0,
    U_SUP_1, U_SUP_2, U_SUP_3, U_SUP_4, U_SUP_5, U_SUP_6, U_SUP_7, U_SUP_8, U_SUP_9, U_SUP_0 */
};



/***********************************************************************************************************************
*
*   UNICODE CHARACTERS
*   These will only be usable if the Windows utility is also installed. Install from:
*   https://github.com/samhocevar/wincompose/releases
*
***********************************************************************************************************************/

// µ
// [U_SNEK]  = 0x1F40D, // 🐍

const uint32_t PROGMEM unicode_map[] = {
    [U_BULLET]  = 0x2022, // •
    [U_COPY]    = 0x00A9, // ©
    [U_DEGREE]  = 0x00B0, // °
    [U_DIVIDE]  = 0x00F7, // ÷
    [U_ELLIPSIS]    = 0x2026, // …

    /*
    [U_FRAC_1_2] = 0x00BD, // ½
    [U_FRAC_1_3]    = 0x2153, // ⅓
    [U_FRAC_2_3]    = 0x2154, // ⅔
    [U_FRAC_1_4] = 0x00BC, // ¼
    [U_FRAC_3_4] = 0x00BE, // ¾
    [U_FRAC_1_8]    = 0x215B, // ⅛
    [U_FRAC_3_8]    = 0x215C, // ⅜
    [U_FRAC_5_8]    = 0x215D, // ⅝
    [U_FRAC_7_8]    = 0x215E, // ⅞
    [U_FRAC_SLASH]  = 0x2044, // ⁄
    */

    [U_INTERROBANG] = 0x203D, // ‽
    [U_PLUSMINUS] = 0x00B1 // ±

    /*
    [U_SUB_1] = 0x2081, // ₁
    [U_SUB_2] = 0x2082, // ₂
    [U_SUB_3] = 0x2083, // ₃
    [U_SUB_4] = 0x2084, // ₄
    [U_SUB_5] = 0x2085, // ₅
    [U_SUB_6] = 0x2086, // ₆
    [U_SUB_7] = 0x2087, // ₇
    [U_SUB_8] = 0x2088, // ₈
    [U_SUB_9] = 0x2089, // ₉
    [U_SUB_0] = 0x2080, // ₀

    [U_SUP_1] = 0x00B9, // ¹
    [U_SUP_2] = 0x00B2, // ²
    [U_SUP_3] = 0x00B3, // ³
    [U_SUP_4] = 0x2074, // ⁴
    [U_SUP_5] = 0x2075, // ⁵
    [U_SUP_6] = 0x2076, // ⁶
    [U_SUP_7] = 0x2077, // ⁷
    [U_SUP_8] = 0x2078, // ⁸
    [U_SUP_9] = 0x2079, // ⁹
    [U_SUP_0] = 0x2070  // ⁰
    */

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
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )/*,

    [L_4] = LAYOUT_stagger(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XP(X(U_SUP_7), X(U_SUB_7)), XP(X(U_SUP_8), X(U_SUB_8)), XP(X(U_SUP_9), X(U_SUB_9)), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XP(X(U_SUP_4), X(U_SUB_4)), XP(X(U_SUP_5), X(U_SUB_5)), XP(X(U_SUP_6), X(U_SUB_6)), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XP(X(U_SUP_1), X(U_SUB_1)), XP(X(U_SUP_2), X(U_SUB_2)), XP(X(U_SUP_3), X(U_SUB_3)), X(U_FRAC_SLASH), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XP(X(U_SUP_0), X(U_SUB_0)), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )*/

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

        /*
        case L_4:
            writePinLow(B7);
            writePinLow(B6);
            rgblight_set_layer_state(GI_FN1, 1);
            rgblight_set_layer_state(GI_FN2, 1);
            break;
        */

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
