/***********************************************************************************************************************
*
*   YOURMATT: Pikatea GB4 Mapping
*   qmk compile -kb yourmatt/pikatea_macropad_gb4 -km yourmatt
*   Enter DFU by: Reset hole on back
*
***********************************************************************************************************************/

// NOTICE: THIS BUILDS, BUT I HAVE NOT LOADED TO THE DEVICE TO TEST - VERSION BUILT AGAINST QMK 0.1.3 IS INSTALLED -
//         REMOVE THIS NOTICE AFTER TESTING

// encoder actions in pikatea_macropad_gb4/pikatea_macropad_gb4.c

#include QMK_KEYBOARD_H

enum custom_keycodes {
    CKC_KVM_INPUT_1, CKC_KVM_INPUT_2, CKC_KVM_INPUT_3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CKC_KVM_INPUT_1, CKC_KVM_INPUT_2, CKC_KVM_INPUT_3, KC_MUTE
    )
};

void keyboard_post_init_user(void) {
    // rgblight_disable();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case CKC_KVM_INPUT_1:
            if (record->event.pressed) {
                tap_code_delay(KC_SCROLL_LOCK, 300);
                tap_code_delay(KC_SCROLL_LOCK, 300);
                tap_code(KC_1);
            }
            return false;
        case CKC_KVM_INPUT_2:
            if (record->event.pressed) {
                tap_code_delay(KC_SCROLL_LOCK, 300);
                tap_code_delay(KC_SCROLL_LOCK, 300);
                tap_code(KC_2);
            }
            return false;
        case CKC_KVM_INPUT_3:
            if (record->event.pressed) {
                tap_code_delay(KC_SCROLL_LOCK, 300);
                tap_code_delay(KC_SCROLL_LOCK, 300);
                tap_code(KC_3);
            }
            return false;

        default:
            return true;

    }
}

/*
bool encoder_update_kb(uint8_t index, bool clockwise) {
    //if (!encoder_update_user(index, clockwise)) {
    //    return false;
    //}
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return true;
}
*/