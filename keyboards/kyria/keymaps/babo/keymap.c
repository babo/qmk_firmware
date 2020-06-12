#include "drashna.h"

uint8_t is_master;

#ifndef UNICODE_ENABLE
#    define UC(x) KC_NO
#endif

/*
 * The `LAYOUT_kyria_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_kyria_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
      KC_ESC,  K01,     K02,     K03,     K04,    K05,                                                           K06,     K07,     K08,     K09,     K0A,     KC_MINS, \
      OS_LSFT, K11,     K12,     K13,     K14,    K15,                                                           K16,     K17,     K18,     K19,     K1A,     MT(OS_RSFT, KC_EQUAL), \
   LALT_T(KC_TAB), LCTL_T(K21),  LGUI_T(K22),     K23,     K24,     K25,     KC_NO, KC_NO,      KC_NO, KC_NO,    K26,     K27,     K28,     RGUI_T(K29), RCTL_T(K2A), RALT_T(KC_QUOT), \
                                 KC_LALT, KC_LGUI, KC_LGUI, DL_RAIS, KC_ENT,                                     ALT_T(KC_SPC), BK_LWER, KC_BSPC, KC_RALT, KC_RGUI \
    )
/* Re-pass though to allow templates to be used */
#define LAYOUT_kyria_base_wrapper(...)       LAYOUT_kyria_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_kyria_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_kyria_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),

    [_WORKMAN] = LAYOUT_kyria_base_wrapper(
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),

    [_NORMAN] = LAYOUT_kyria_base_wrapper(
        _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
        _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
        _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
    ),

    [_MODS] = LAYOUT_wrapper(
        _______, ___________________BLANK___________________,                                       ___________________BLANK___________________, _______,
        KC_LSFT, ___________________BLANK___________________,                                       ___________________BLANK___________________, KC_RSFT,
        _______, ___________________BLANK___________________, _______, _______,   _______, _______, ___________________BLANK___________________, _______,
                                   _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
    ),
    [_LOWER] = LAYOUT_wrapper(
        KC_TILDE, _________________LOWER_L1__________________,                                       _________________LOWER_R1__________________, KC_PIPE,
        _______,  _________________LOWER_L2__________________,                                       _________________LOWER_R2__________________, _______,
        _______,  _________________LOWER_L3__________________, _______, _______,   _______, _______, _________________LOWER_R3__________________, _______,
                                    _______, _______, _______, _______, _______,   _______, _______, KC_DELETE, _______, _______
    ),
    [_RAISE] = LAYOUT_wrapper(
        KC_GRAVE, _________________RAISE_L1__________________,                                       _________________RAISE_R1__________________, KC_BSLS,
        _______,  _________________RAISE_L2__________________,                                       _________________RAISE_R2__________________, _______,
        _______,  _________________RAISE_L3__________________, _______, _______,   _______, _______, _________________RAISE_R3__________________, _______,
                                    _______, _______, _______, _______, _______,   _______, _______, KC_DELETE, _______, _______
    ),
    [_ADJUST] = LAYOUT_wrapper(
        KC_MAKE, _________________ADJUST_L1_________________,                                       _________________ADJUST_R1_________________, KC_RESET,
        VRSN,    _________________ADJUST_L2_________________,                                       _________________ADJUST_R2_________________, EEP_RST,
        _______, _________________ADJUST_L3_________________, _______, _______,   _______, _______, _________________ADJUST_R3_________________, TG_MODS,
                                   _______, _______, _______, UC_SHRG, _______,   MG_NKRO, UC_MOD,  _______, _______, _______
    ),
//     [_LAYERINDEX] = LAYOUT_wrapper(
//       _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
//     ),
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
