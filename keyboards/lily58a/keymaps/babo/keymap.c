#include "drashna.h"

uint8_t is_master;

/*
 * The `LAYOUT_lily58_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_lily58_base( \
        K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
        K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
        K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A,  \
        K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A  \
    ) \
    LAYOUT_wrapper( \
        KC_ESC,  K01, K02, K03, K04, K05,                    K06, K07, K08, K09, K0A, KC_BSLASH,  \
        KC_GRAVE,  K11, K12, K13, K14, K15,                    K16, K17, K18, K19, K1A, KC_MINS, \
        OS_LSFT, K21, K22, K23, K24, K25,                    K26, K27, K28, K29, K2A, MT(OS_RSFT, KC_EQUAL), \
        LALT_T(KC_TAB), LCTL_T(K31), LGUI_T(K32), K33, K34, K35, OS_LSFT, OS_RSFT,  K36, K37, K38, RGUI_T(K39), RCTL_T(K3A), RALT_T(KC_QUOT), \
                 KC_LCTL, KC_LGUI, DL_RAIS, GUI_T(KC_ENT),  ALT_T(KC_SPC),   BK_LWER, KC_BSPC, KC_LALT           \
    )
#define LAYOUT_lily58_base_wrapper(...) LAYOUT_lily58_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_lily58_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_lily58_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),

    [_WORKMAN] = LAYOUT_lily58_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),

    [_NORMAN] = LAYOUT_lily58_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
        _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
        _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
    ),

    [_MODS] = LAYOUT_wrapper(
        _______, ___________________BLANK___________________,                    ___________________BLANK___________________, _______,
        _______, ___________________BLANK___________________,                    ___________________BLANK___________________, _______,
        _______, ___________________BLANK___________________,                    ___________________BLANK___________________, _______,
        _______, ___________________BLANK___________________, _______,  _______, ___________________BLANK___________________, _______,
                                   _______, _______, _______, _______,  _______, _______, _______, _______
    ),

    [_LOWER] = LAYOUT_wrapper( \
        _______, ___________________BLANK___________________,                    ___________________BLANK___________________, _______,
        KC_TILDE,  _________________LOWER_L1__________________,                    _________________LOWER_R1__________________, _______,
        _______, _________________LOWER_L2__________________,                    _________________LOWER_R2__________________, _______,
        _______, _________________LOWER_L3__________________, _______,  _______, _________________LOWER_R3__________________, _______,
                                   _______, _______, _______, _______,  _______, _______, KC_DELETE, _______
    ),

    [_RAISE] = LAYOUT_wrapper( \
        _______, ___________________BLANK___________________,                    ___________________BLANK___________________, _______,
        KC_GRAVE, _________________RAISE_L1__________________,                    _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________,                    _________________RAISE_R2__________________, _______,
        _______, _________________RAISE_L3__________________, _______,  _______, _________________RAISE_R3__________________, _______,
                                   _______, _______, _______, _______,  _______, _______, KC_DELETE, _______
    ),

    [_ADJUST] = LAYOUT_wrapper( \
        _______, ___________________BLANK___________________,                    ___________________BLANK___________________, _______,
        KC_MAKE, _________________ADJUST_L1_________________,                    _________________ADJUST_R1_________________, KC_RST,
        VRSN,    _________________ADJUST_L2_________________,                    _________________ADJUST_R2_________________, EEP_RST,
        MG_NKRO, _________________ADJUST_L3_________________, _______,  _______, _________________ADJUST_R3_________________, RGB_IDL,
                                   _______, _______, _______, _______,  _______, _______, _______, _______
    ),
};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifndef SPLIT_KEYBOARD
        if (keycode == RESET && !is_master) {
            return false;
        }
#endif
    }
    return true;
}

void matrix_init_keymap(void) { is_master = (uint8_t)is_keyboard_master(); }

