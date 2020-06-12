#include QMK_KEYBOARD_H

#include "drashna.h"

// Default Arch40 keymap
// qwerty ansi-style base layer, arrows
// layer1 = numbers, operators, nav, media
// layer2 = function keys, symbols, rgb control, reset

#define base 0
#define layer1 1
#define layer2 2

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

//Tap Dance Declarations
enum tap_dances {
  TD_ESC_TAB = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* base
 *       .-----------------------------------------------------------------------------.
 *       | ESC |  Q  |  W  |  E  |  R  |  T  |     |  Y  |  U  |  I  |  O  |  P  | BKSP|
 *       |-----------------------------------------------------------------------------|
 *       | TAB |  A  |  S  |  D  |  F  |  G  | LT2 |  H  |  J  |  K  |  L  |  ;  | QUO |
 *       |-----------------------------------------------------------------------------|
 *       | SFT |  Z  |  X  |  C  |  V  |  B  | LT1 |  N  |  M  |  ,  |  .  |  /  | ENT |
 *       |-----------------------------------------------------------------------------|
 *       | CTL |     | ALT | GUI | LT1 | LT2 | SPC | LEFT| DOWN|  UP | RGHT|     | SFT |
 *       `-----------------------------------------------------------------------------`
*/

  [_QWERTY] = LAYOUT(
    TD(TD_ESC_TAB),   KC_Q,     KC_W,     KC_E,     KC_R,          KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC ,
    KC_LSPO,  KC_A,     KC_S,     KC_D,     KC_F,          KC_G,          KC_SPC, KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_SFTENT,
    KC_LCTL,  KC_Z,     KC_X,     KC_C,     KC_V,          KC_B,          KC_SPC, KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_QUOT,
    KC_LALT,            KC_LALT,  KC_LGUI,  RAISE, LOWER, KC_ENT,        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,            KC_ENT ),

  [_COLEMAK] = LAYOUT(
    TD(TD_ESC_TAB),   KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,          KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN,  KC_BSPC ,
    KC_LSFT,   KC_A   , KC_R   , KC_S   , KC_T   , KC_G   , KC_SPC, KC_M   , KC_N   , KC_E   , KC_I   , KC_O   ,  KC_SFTENT ,
    KC_LCTL,   KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , KC_SPC, KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH,  KC_QUOT ,
    KC_LALT,            KC_LALT,  KC_LGUI,  RAISE, LOWER, KC_ENT,        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,            KC_ENT ),

/* layer1
 *       .-----------------------------------------------------------------------------.
 *       |  `  |  1  |  2  |  3  |  4  |  5  |     |  6  |  7  |  8  |  9  |  0  | DEL |
 *       |-----------------------------------------------------------------------------|
 *       |     | PGD | PGU | HOM | END |  _  |     |  =  |  -  |  +  |  (  |  )  |  \  |
 *       |-----------------------------------------------------------------------------|
 *       | CPS | Vl- | Vl+ |     |     |     |     |     |     |     |     |     |     |
 *       |-----------------------------------------------------------------------------|
 *       |     |     |     |     |     |     |     |     |     |     |     |     |     |
 *       `-----------------------------------------------------------------------------`
*/

  [_LOWER] = LAYOUT(
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                 KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL  ,
    _______,  KC_PGDN,  KC_PGUP,  KC_HOME,  KC_END,   KC_UNDS,  _______,  KC_EQL,   KC_MINS,  KC_PLUS,  KC_LPRN,  KC_RPRN,  KC_BSLS ,
    KC_CAPS,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______ ,
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______ ),

/* layer2
 *       .-----------------------------------------------------------------------------.
 *       |  ~  |   1 |   2 |   3 |   4 |   5 |     |   6 |   7 |   8 |   9 |   0 |  `  |
 *       |-----------------------------------------------------------------------------|
 *       |     |  !  |  @  |  #  |  $  |  %  |     |  ^  |  &  |  *  |  [  |  ]  |  |  |
 *       |-----------------------------------------------------------------------------|
 *       |     | Va- | Va+ | Hu+ | Hu- | Tog |     |     |  (  |  )  |  {  |  }  |     |
 *       |-----------------------------------------------------------------------------|
 *       |     |     |     | Sa+ | Sa- |     |     |     |     |     |     |     |     |
 *       `-----------------------------------------------------------------------------`
 *
 *      Tog = RGB_TOG (Toggle under glow)
 *      Sa+ = RGB_SAI (Increase hue)
 *      Sa- = RGB_SAD (Decrease saturation)
 *      Hu+ = RGB_HUI (Increase hue)
 *      Hu- = RGB_HUD (Decrease hue)
 *      Va+ = RGB_VAI (Increase value/brightness)
 *      Va- = RGB_VAD (Decrease value/brightness)
 *
*/

  [_RAISE] = LAYOUT(
    KC_TILD,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_GRV  ,
    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LBRC,  KC_RBRC,  KC_PIPE ,
    _______,  RGB_VAD,  RGB_VAI,  RGB_HUI,  RGB_HUD,  RGB_TOG,  _______,  _______,  KC_LPRN,  KC_RPRN,  KC_LCBR,  KC_RCBR,  _______ ,
    _______,            _______,  RGB_SAI,  RGB_SAD,  _______,  _______,  _______,  _______,  _______,  _______,            _______ ),


  [_ADJUST] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______ ,
    _______,  _______,  _______,  _______,  COLEMAK,  _______,  _______,   QWERTY,  _______,  _______,  _______,  _______,  _______ ,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET   )
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for tilde
  [TD_ESC_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC)
// Other declarations would go here, separated by commas, if you have them
};
