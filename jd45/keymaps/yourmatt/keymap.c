/***********************************************************************************************************************
*
*   YOURMATT: JD45 Mapping
*   qmk compile -kb yourmatt/jd45 -km yourmatt
*   Enter DFU by: LShift + RShift + B
*
***********************************************************************************************************************/

#include QMK_KEYBOARD_H
#include "strings.c"

/* TODO:

*/



/***********************************************************************************************************************
*
*   CONSTANTS
*
***********************************************************************************************************************/

enum layer_indexes {
    L_DEFAULT, L_1, L_2, L_3
};

enum custom_keycodes {
    CKC_PASS = SAFE_RANGE
};



/***********************************************************************************************************************
*
*   KEYMAP
*
***********************************************************************************************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [L_DEFAULT] = LAYOUT(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET,
        KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, KC_RSFT,
        KC_TRNS, MO(L_1), KC_LALT, KC_LGUI, LT(L_3, KC_BSPACE), KC_SPC, KC_RGUI, KC_RALT, MO(L_2), KC_TRNS
    ),

    [L_1] = LAYOUT(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_QUOTE, KC_TRNS,
        KC_TRNS, DYN_REC_START1, DYN_REC_STOP, DYN_MACRO_PLAY1, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_BSLASH, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_INSERT, KC_TAB, KC_0, KC_PGDN, KC_TRNS, KC_TRNS
    ),

    [L_2] = LAYOUT(
        KC_CAPSLOCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_TRNS, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_PAUSE, KC_TRNS,
        KC_TRNS, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_TRNS, KC_LEFT, KC_RIGHT, KC_TRNS, KC_PSCREEN, CKC_PASS,
        KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_DEL, KC_TRNS, KC_DOWN, KC_END, KC_TRNS, KC_TRNS
    ),

    [L_3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_LEFT), KC_PGDN, KC_PGUP, LCTL(KC_RIGHT), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, LCTL(KC_END), LCTL(KC_HOME), KC_END, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )

};


/***********************************************************************************************************************
*
*   STATICS
*
***********************************************************************************************************************/

// each are set to true when holding the related key
static bool H_LCTRL = false;


/***********************************************************************************************************************
*
*   KEYPRESS EVENTS
*
***********************************************************************************************************************/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case KC_LCTRL:

            // hold status of press for ctrl macros
            H_LCTRL = record->event.pressed;

            return true;
        case KC_SPC:

            // set caps lock for ctrl+space
            if (record->event.pressed) {
                if (H_LCTRL) {
                    register_code(KC_CAPSLOCK);
                    return false;
                }
            }

            return true;
        // custom keycodes
        case CKC_PASS:
            if (record->event.pressed) {
                SEND_STRING(PASSWORD1);
            }
            return true;

        default:
            return true;

    }
}