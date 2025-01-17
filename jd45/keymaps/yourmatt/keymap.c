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
Remove Ctrl Space for caps - Now using left space + right space
*/


/***********************************************************************************************************************
*
*   CONSTANTS
*
***********************************************************************************************************************/

enum layer_indexes {
    L_DEFAULT, L_1, L_2, L_3, L_4
};
enum unicode_names {
    U_ARROW_CCW, U_ARROW_CW, U_ARROW_DOWN, U_ARROW_LEFT, U_ARROW_RIGHT, U_ARROW_UP, U_BULLET, U_CENTS, U_CHECKMARK,
    U_COPY, U_DEGREE, U_DIVIDE, U_ELLIPSIS, U_ELLIPSIS_VERT, U_INTERROBANG, U_MICRO, U_PLUSMINUS, U_REG, U_SKULL,
    U_STAR_FILLED, U_STAR_OUTLINE, U_TIMES, U_TRIANGLE_DOWN, U_TRIANGLE_LEFT, U_TRIANGLE_RIGHT, U_TRIANGLE_UP,
    U_E_EYEROLL, U_E_JOY, U_E_KISS, U_E_LOVE, U_E_ROFL, U_E_SMILE, U_E_THINK
};
enum custom_keycodes {
    CKC_PASS = SAFE_RANGE,
    CKC_MACRO_LIST_TO_CSV
};



/***********************************************************************************************************************
*
*   UNICODE CHARACTERS
*   These will only be usable if the Windows utility is also installed. Install from:
*   https://github.com/samhocevar/wincompose/releases
*
***********************************************************************************************************************/

const uint32_t PROGMEM unicode_map[] = {

    // unicode
    [U_ARROW_CCW] = 0x21BA,         // ↺
    [U_ARROW_CW] = 0x21BB,          // ↻
    [U_ARROW_DOWN] = 0x2193,        // ↓	menu
    [U_ARROW_LEFT] = 0x2190,        // ←	m
    [U_ARROW_RIGHT] = 0x2192,       // →	,
    [U_ARROW_UP] = 0x2191,          // ↑	k
    [U_BULLET] = 0x2022,            // •	b
    [U_CENTS] = 0x00A2,             // ¢	f
    [U_CHECKMARK] = 0x2713,         // ✓	v
    [U_COPY] = 0x00A9,              // ©	c
    [U_DEGREE] = 0x00B0,            // °	d
    [U_DIVIDE] = 0x00F7,            // ÷	p
    [U_ELLIPSIS] = 0x2026,          // …	.
    [U_ELLIPSIS_VERT] = 0x22EE,     // ⋮	rshift
    [U_INTERROBANG] = 0x203D,       // ‽	a
    [U_MICRO] = 0x00B5,             // µ
    [U_PLUSMINUS] = 0x00B1,         // ±	]
    [U_REG] = 0x00AE,               // ®	r
    [U_SKULL] = 0x2620,             // ☠	esc
    [U_STAR_FILLED] = 0x2605,       // ★	q
    [U_STAR_OUTLINE] = 0x2606,      // ☆	w
    [U_TIMES] = 0x00D7,             // ×	x
    [U_TRIANGLE_DOWN] = 0x23F7,     // ⏷	/
    [U_TRIANGLE_LEFT] = 0x23F4,     // ⏴	;
    [U_TRIANGLE_RIGHT] = 0x23F5,    // ⏵	enter
    [U_TRIANGLE_UP] = 0x23F6,       // ⏶	[

    // emojis
    [U_E_EYEROLL] = 0x1F644,        // 🙄	ctrl
    [U_E_JOY] = 0x1F602,            // 😂	backspace
    [U_E_KISS] = 0x1F618,           // 😘	lalt
    [U_E_LOVE] = 0x1F60D,           // 😍	win
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
    C_FRAC_1_3, C_FRAC_2_3,
    C_FRAC_1_4, C_FRAC_3_4,
    C_FRAC_1_5,
    C_FRAC_2_5, C_FRAC_3_5, C_FRAC_4_5,
    C_FRAC_1_6, C_FRAC_5_6,
    C_FRAC_1_7,
    C_FRAC_1_8, C_FRAC_3_8, C_FRAC_5_8, C_FRAC_7_8,
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

combo_t key_combos[] = {
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

    /* BASE LAYER
       ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
       │  Esc  │  q Q  │  w W  │  e E  │  r R  │  t T  │  y Y  │  u U  │  i I  │  o O  │  p P  │  [ {  │  ] }  │
       ├───────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴───────┤
       │  Ctrl   │  a A  │  s S  │  d D  │  f F  │  g G  │  h H  │  j J  │  k K  │  l L  │  ; :  │    Enter    │
       ├─────────┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬─────────┤
       │    Shift    │  z Z  │  x X  │  c C  │  v V  │  b B  │  n N  │  m M  │  , <  │  . >  │  / ?  │  Shift  │
       ╰─────────┬───┴───┬───┴─────┬─┴───────┼───────┴─────┬─┴───────┴───┬───┴─────┬─┴───────┼───────┼─────────╯
                 │Layer1 │   Alt   │   Win   │  Backspace  │    Space    │  Menu   │   Alt   │Layer2 │
                 ╰───────┴─────────┴─────────┴─────────────┴─────────────┴─────────┴─────────┴───────╯        */
    [L_DEFAULT] = LAYOUT(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_RIGHT_BRACKET,
        KC_LEFT_CTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, KC_RSFT,
        KC_TRNS, MO(L_1), KC_LALT, KC_LGUI, LT(L_4, KC_BACKSPACE), KC_SPC, KC_RGUI, KC_RALT, MO(L_2), KC_TRNS
    ),

    /* LAYER 1 - HOLDING LEFT MOD
       Additional features: 1) Fractions by pressing two numbers together
                            2) Superscript numbers by holding shift and pressing number
                            3) Subscript numbers by holding control and pressing number (plus backslash for ⁄)
       ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
       │  ` ~  │   1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │   0   │  - _  │  = +  │
       ├───────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴───────┤
       │         │Lst2CSV│ColrPck│FncZons│       │       │       │   4   │   5   │   6   │  ' "  │             │
       ├─────────┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬─────────┤
       │             │McroRec│McroStp│McroPly│       │       │       │   1   │   2   │   3   │  \ |  │         │
       ╰─────────┬───┴───┬───┴─────┬─┴───────┼───────┴─────┬─┴───────┴───┬───┴─────┬─┴───────┼───────┼─────────╯
                 │ ░░░░░ │  Home   │         │   Insert    │     Tab     │    0    │  PgDn   │Layer3 │
                 ╰───────┴─────────┴─────────┴─────────────┴─────────────┴─────────┴─────────┴───────╯        */
    [L_1] = LAYOUT(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL,
        KC_TRNS, CKC_MACRO_LIST_TO_CSV, SWIN(KC_C), LWIN(KC_GRAVE), KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_QUOTE, KC_TRNS,
        KC_TRNS, QK_DYNAMIC_MACRO_RECORD_START_1, QK_DYNAMIC_MACRO_RECORD_STOP, QK_DYNAMIC_MACRO_PLAY_1, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_BACKSLASH, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_INSERT, KC_TAB, KC_0, KC_PGDN, OSL(L_3), KC_TRNS
    ),

    /* LAYER 2 - HOLDING RIGHT MOD
       ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
       │ Caps  │  F1   │  F2   │  F3   │  F4   │  F5   │  F6   │  F7   │  F8   │  F9   │  F10  │  F11  │  F12  │
       ├───────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴───────┤
       │         │   !   │   @   │   #   │   $   │   %   │       │       │  Up   │       │ Pause │             │
       ├─────────┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬─────────┤
       │             │   ^   │   &   │   *   │   (   │   )   │       │ Left  │ Right │       │ PtScr │  Pass   │
       ╰─────────┬───┴───┬───┴─────┬─┴───────┼───────┴─────┬─┴───────┴───┬───┴─────┬─┴───────┼───────┼─────────╯
                 │Layer3 │  PgUp   │         │   Delete    │             │  Down   │   End   │ ░░░░░ │
                 ╰───────┴─────────┴─────────┴─────────────┴─────────────┴─────────┴─────────┴───────╯        */
    [L_2] = LAYOUT(
        KC_CAPS_LOCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_TRNS, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_PAUSE, KC_TRNS,
        KC_TRNS, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_TRNS, KC_LEFT, KC_RIGHT, KC_TRNS, KC_PRINT_SCREEN, CKC_PASS,
        KC_TRNS, OSL(L_3), KC_PGUP, KC_TRNS, KC_DEL, KC_TRNS, KC_DOWN, KC_END, KC_TRNS, KC_TRNS
    ),

    /* LAYER 3 - ONE-SHOT KEY AFTER PRESSING LEFT AND RIGHT MODS
       ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
       │   ☠   │   ★   │   ☆  │       │   ®   │       │       │       │       │       │   ÷   │   ⏶   │   ±   │
       ├───────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴───────┤
       │   🙄    │   ‽   │       │   °   │   ¢   │       │       │       │   ↑   │       │   ⏴  │      ⏵      │
       ├─────────┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬─────────┤
       │     🤔      │       │   ×   │   ©   │   ✓   │   •   │       │   ←   │   →   │   …   │   ⏷  │    ⋮     │
       ╰─────────┬───┴───┬───┴─────┬─┴───────┼───────┴─────┬─┴───────┴───┬───┴─────┬─┴───────┼───────┼─────────╯
                 │       │   😘    │   😍    │     😂     │      😀     │    ↓    │   🤣    │       │
                 ╰───────┴─────────┴─────────┴─────────────┴─────────────┴─────────┴─────────┴───────╯        */
    [L_3] = LAYOUT(
        X(U_SKULL), X(U_STAR_FILLED), X(U_STAR_OUTLINE), KC_TRNS, X(U_REG), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, X(U_DIVIDE), X(U_TRIANGLE_UP), X(U_PLUSMINUS),
        X(U_E_EYEROLL), X(U_INTERROBANG), KC_TRNS, X(U_DEGREE), X(U_CENTS), KC_TRNS, KC_TRNS, KC_TRNS, X(U_ARROW_UP), KC_TRNS, X(U_TRIANGLE_LEFT), X(U_TRIANGLE_RIGHT),
        X(U_E_THINK), KC_TRNS, X(U_TIMES), X(U_COPY), X(U_CHECKMARK), X(U_BULLET), KC_TRNS, X(U_ARROW_LEFT), X(U_ARROW_RIGHT), X(U_ELLIPSIS), X(U_TRIANGLE_DOWN), X(U_ELLIPSIS_VERT),
        KC_TRNS, KC_TRNS, X(U_E_KISS), X(U_E_LOVE), X(U_E_JOY), X(U_E_SMILE), X(U_ARROW_DOWN), X(U_E_ROFL), KC_TRNS, KC_TRNS
    ),

    /* LAYER 4 - HOLDING LEFT SPACEBAR
       ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
       │       │       │       │       │       │       │       │   -   │   _   │   +   │   =   │       │       │
       ├───────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴───────┤
       │         │       │       │       │       │       │ Left  │ Down  │  Up   │ Right │       │             │
       ├─────────┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬───┴───┬─────────┤
       │             │       │       │       │       │ Home  │LeftWrd│ PgDn  │ PgUp  │RghtWrd│  End  │         │
       ╰─────────┬───┴───┬───┴─────┬─┴───────┼───────┴─────┬─┴───────┴───┬───┴─────┬─┴───────┼───────┼─────────╯
                 │       │         │         │ ░░░░░░░░░░░ │    Caps     │         │         │       │
                 ╰───────┴─────────┴─────────┴─────────────┴─────────────┴─────────┴─────────┴───────╯        */
    [L_4] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINUS, KC_UNDERSCORE, KC_PLUS, KC_EQUAL, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, LCTL(KC_LEFT), KC_PGDN, KC_PGUP, LCTL(KC_RIGHT), KC_END, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS_LOCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )

};



/***********************************************************************************************************************
*
*   STATICS
*
***********************************************************************************************************************/

// each are set to true when holding the related key
static bool H_LCTRL = false;
static bool H_SHIFT = false;



/***********************************************************************************************************************
*
*   KEYPRESS EVENTS
*
***********************************************************************************************************************/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        // hold status of press for ctrl macros
        case KC_LEFT_CTRL:
            H_LCTRL = record->event.pressed;
            return true;

        // hold status of press for superscript numbers
        case KC_LEFT_SHIFT:
            H_SHIFT = record->event.pressed;
            return true;

        // set caps lock for ctrl+space
        case KC_SPC:
            if (record->event.pressed) {
                if (H_LCTRL) {
                    register_code(KC_CAPS_LOCK);
                    return false;
                }
            }
            return true;

        // set super and subscript for all numbers
        case KC_1:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("¹"); return false; }
                else if (H_LCTRL) { send_unicode_string("₁"); return false; }
            }
            return true;
        case KC_2:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("²"); return false; }
                else if (H_LCTRL) { send_unicode_string("₂"); return false; }
            }
            return true;
        case KC_3:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("³"); return false; }
                else if (H_LCTRL) { send_unicode_string("₃"); return false; }
            }
            return true;
        case KC_4:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁴"); return false; }
                else if (H_LCTRL) { send_unicode_string("₄"); return false; }
            }
            return true;
        case KC_5:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁵"); return false; }
                else if (H_LCTRL) { send_unicode_string("₅"); return false; }
            }
            return true;
        case KC_6:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁶"); return false; }
                else if (H_LCTRL) { send_unicode_string("₆"); return false; }
            }
            return true;
        case KC_7:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁷"); return false; }
                else if (H_LCTRL) { send_unicode_string("₇"); return false; }
            }
            return true;
        case KC_8:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁸"); return false; }
                else if (H_LCTRL) { send_unicode_string("₈"); return false; }
            }
            return true;
        case KC_9:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁹"); return false; }
                else if (H_LCTRL) { send_unicode_string("₉"); return false; }
            }
            return true;
        case KC_0:
            if (record->event.pressed) {
                if (H_SHIFT) { send_unicode_string("⁰"); return false; }
                else if (H_LCTRL) { send_unicode_string("₀"); return false; }
            }
            return true;
        case KC_BACKSLASH:
            if (record->event.pressed && H_LCTRL) { send_unicode_string("⁄"); return false; }
            return true;

        // custom keycodes
        case CKC_PASS:
            if (record->event.pressed) {
                SEND_STRING(PASSWORD1);
            }
            return true;

        // in Notepad, take a list of items and convert to a comma-separated list, then cut it to clipboard
        // move up, end, select to start of next line, ctrl-h, tap, typing the comma in the replacement field, alt-a, esc, ctrl-a, ctrl-x
        case CKC_MACRO_LIST_TO_CSV:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_UP) SS_TAP(X_END) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT));
                SEND_STRING(SS_DOWN(X_LEFT_CTRL) "h" SS_UP(X_LEFT_CTRL));
                SEND_STRING(SS_TAP(X_TAB) "," SS_DOWN(X_LALT) "a" SS_UP(X_LALT));
                SEND_STRING(SS_TAP(X_ESC));
                SEND_STRING(SS_DOWN(X_LEFT_CTRL) "a" SS_UP(X_LEFT_CTRL));
                SEND_STRING(SS_DOWN(X_LEFT_CTRL) "x" SS_UP(X_LEFT_CTRL));
            }
            return true;

        default:
            return true;

    }
}