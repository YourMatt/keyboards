/***********************************************************************************************************************
*
*   YOURMATT: Pikatea GB4 Mapping
*   qmk compile -kb yourmatt/pikatea_macropad_gb4 -km yourmatt
*   Enter DFU by: Reset hole on back
*
***********************************************************************************************************************/

// encoder actions in pikatea_macropad_gb4/pikatea_macropad_gb4.c

#include QMK_KEYBOARD_H

enum custom_keycodes {
    CKC_KVM_INPUT_1, CKC_KVM_INPUT_2, CKC_KVM_INPUT_3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CKC_KVM_INPUT_1, CKC_KVM_INPUT_2, CKC_KVM_INPUT_3, KC_MUTE
    )
};

void keyboard_post_init_user(void) {
    rgblight_disable();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

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

        default:
            return true;

    }
}