#include "pebble.h"

enum unicode_names {
    A_AC,
    E_AC,
    I_AC,
    O_AC,
    O_DA,
    O_DI,
    U_AC,
    U_DA,
    U_DI,
    a_AC,
    e_AC,
    i_AC,
    o_AC,
    o_DA,
    o_DI,
    u_AC,
    u_DA,
    u_DI,
};

// 00C1	Á	00E1	á	A acute
// 00C9	É	00E9	é	E acute
// 00D6	Ö	00F6	ö	O diaeresis
// 00D3	Ó	00F3	ó	O acute
// 0150	Ő	0151	ő	O double acute
// 00CD	Í	00ED	í	I acute
// 00DC	Ü	00FC	ü	U diaeresis
// 00DA	Ú	00FA	ú	U acute
// 0170	Ű	0171	ű	U double acute

const uint32_t PROGMEM unicode_map[] = {
    [A_AC] = 0x00C1,
    [E_AC] = 0x00C9,
    [I_AC] = 0x00ED,
    [O_AC] = 0x00D3,
    [O_DA] = 0x0150,
    [O_DI] = 0x00D6,
    [U_AC] = 0x00DA,
    [U_DA] = 0x0170,
    [U_DI] = 0x00DC,

    [a_AC] = 0x00E1,
    [e_AC] = 0x00E9,
    [i_AC] = 0x00ED,
    [o_AC] = 0x00F3,
    [o_DA] = 0x0151,
    [o_DI] = 0x00F6,
    [u_AC] = 0x00FA,
    [u_DA] = 0x0171,
    [u_DI] = 0x00FC,
};

#define AAC XP(a_AC, A_AC)
#define EAC XP(e_AC, E_AC)
#define IAC XP(i_AC, I_AC)
#define OAC XP(o_AC, O_AC)
#define ODA XP(o_DA, O_DA)
#define ODI XP(o_DI, O_DI)
#define UAC XP(u_AC, U_AC)
#define UDA XP(u_DA, U_DA)
#define UDI XP(u_DI, U_DI)

#define LAYOUT_miryoku( \
       K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09, \
       K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19, \
       K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29, \
       N30,   N31,   K32,   K33,   K34,   K35,   K36,   K37,   N38,   N39 \
) \
LAYOUT( \
    KC_NO, EAC, AAC, IAC, OAC,  UAC, \
    ODI, K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   UDI, \
    KC_LSFT, K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   KC_RSFT, \
    ODA, K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   UDA, \
    K32,   K33,   K34,   KC_SPC, KC_BSPC, K35,   K36,   K37 \
)

#define KC_NP KC_NO // key is not present
#define KC_NA KC_NO // present but not available for use
#define KC_NU KC_NO // available but not used

// non-KC_ keycodes
#define KC_RST RESET
#define KC_TOG RGB_TOG
#define KC_MOD RGB_MOD
#define KC_HUI RGB_HUI
#define KC_SAI RGB_SAI
#define KC_VAI RGB_VAI

enum layers { BASE, MBO, MEDR, NAVR, MOUR, NSSL, NSL, FUNL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#if defined MIRYOKU_BASE_QWERTY
  [BASE] = LAYOUT_miryoku(
    KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,
    LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_QUOT),
    KC_Z,              ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
    KC_NP,             KC_NP,             LT(MEDR, KC_ESC),  LT(NAVR, KC_ENT),  LT(MOUR, KC_TAB),  LT(NSSL, KC_BSPC),  LT(NSL, KC_SPC),  LT(FUNL, KC_DEL),  KC_NP,             KC_NP
  ),
#elif defined MIRYOKU_BASE_DVORAK
  [BASE] = LAYOUT_miryoku(
    KC_QUOT,           KC_COMM,           KC_DOT,            KC_P,              KC_Y,              KC_F,              KC_G,              KC_C,              KC_R,              KC_L,
    LGUI_T(KC_A),      LALT_T(KC_O),      LCTL_T(KC_E),      LSFT_T(KC_U),      KC_I,              KC_D,              LSFT_T(KC_H),      LCTL_T(KC_T),      LALT_T(KC_N),      LGUI_T(KC_S),
    KC_SLSH,           ALGR_T(KC_Q),      KC_J,              KC_K,              KC_X,              KC_B,              KC_M,              KC_W,              ALGR_T(KC_V),      KC_Z,
    KC_NP,             KC_NP,             LT(MEDR, KC_ESC),  LT(NAVR, KC_SPC),  LT(MOUR, KC_TAB),  LT(NSSL, KC_ENT),  LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_NP,             KC_NP
  ),
#elif defined MIRYOKU_BASE_COLEMAK
  [BASE] = LAYOUT_miryoku(
    KC_Q,              KC_W,              KC_F,              KC_P,              KC_G,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
    LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_D,              KC_H,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),
    KC_Z,              ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_K,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
    KC_NP,             KC_NP,             LT(MEDR, KC_ESC),  LT(NAVR, KC_SPC),  LT(MOUR, KC_TAB),  LT(NSSL, KC_ENT),  LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_NP,             KC_NP
  ),
#elif defined MIRYOKU_BASE_COLEMAKDH
  [BASE] = LAYOUT_miryoku(
    KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
    LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_K,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),
    KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_M,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
    KC_NP,             KC_NP,             LT(MEDR, KC_ESC),  LT(NAVR, KC_SPC),  LT(MOUR, KC_TAB),  LT(NSSL, KC_ENT),  LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_NP,             KC_NP
  ),
#elif defined MIRYOKU_BASE_WORKMAN
  [BASE] = LAYOUT_miryoku(
    KC_Q,              KC_D,              KC_R,              KC_W,              KC_B,              KC_J,              KC_F,              KC_U,              KC_P,              KC_QUOT,
    LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_H),      LSFT_T(KC_T),      KC_G,              KC_Y,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_O),      LGUI_T(KC_I),
    KC_Z,              ALGR_T(KC_X),      KC_M,              KC_C,              KC_V,              KC_K,              KC_L,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
    KC_NP,             KC_NP,             LT(MEDR, KC_ESC),  LT(NAVR, KC_SPC),  LT(MOUR, KC_TAB),  LT(NSSL, KC_ENT),  LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_NP,             KC_NP
  ),
#else
  [BASE] = LAYOUT_miryoku(
    KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
    LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),
    KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
    KC_NP,             KC_NP,             LT(MEDR, KC_ESC),  LT(NAVR, KC_SPC),  LT(MOUR, KC_TAB),  LT(NSSL, KC_BSPC),  LT(NSL, KC_ENT),  LT(FUNL, KC_DEL),  KC_NP,             KC_NP
  ),
#endif
  [NAVR] = LAYOUT_miryoku(
    KC_RST,  KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_AGIN, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NA,   KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_NA,   KC_ALGR, KC_NA,   KC_NA,   KC_NA,   KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    KC_NP,   KC_NP,   KC_NA,   KC_NA,   KC_NA,   KC_ENT,  KC_BSPC, KC_DEL,  KC_NP,   KC_NP
  ),
  [MOUR] = LAYOUT_miryoku(
    KC_RST,  KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NA,   KC_NU,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
    KC_NA,   KC_ALGR, KC_NA,   KC_NA,   KC_NA,   KC_NU,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
    KC_NP,   KC_NP,   KC_NA,   KC_NA,   KC_NA,   KC_BTN1, KC_BTN3, KC_BTN2, KC_NP,   KC_NP
  ),
  [MBO] = LAYOUT_miryoku(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_NP,   KC_NP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_NP,   KC_NP
  ),
  [MEDR] = LAYOUT_miryoku(
    KC_RST,  KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_TOG,  KC_MOD,  KC_HUI,  KC_SAI,  KC_VAI,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NA,   KC_NU,   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
    KC_NA,   KC_ALGR, KC_NA,   KC_NA,   KC_NA,   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,
    KC_NP,   KC_NP,   KC_NA,   KC_NA,   KC_NA,   KC_MSTP, KC_MPLY, KC_MUTE, KC_NP,   KC_NP
  ),
  [FUNL] = LAYOUT_miryoku(
    KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, UNICODE_MODE_MAC,  KC_NA,   KC_NA,   KC_NA,   KC_RST,
    KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, UNICODE_MODE_LNX,  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, UNICODE_MODE_WIN,  KC_NA,   KC_NA,   KC_ALGR, KC_NA,
    KC_NP,   KC_NP,   KC_APP,  KC_SPC,  KC_TAB,  KC_NA,             KC_NA,   KC_NA,   KC_NP,   KC_NP
  ),
  [NSL] = LAYOUT_miryoku(
    KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, KC_NA, KC_NA,   KC_NA,   KC_NA,   KC_RST,
    KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,  KC_NA, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, KC_NA, KC_NA,   KC_NA,   KC_ALGR, KC_NA,
    KC_NP,   KC_NP,   KC_DOT,  KC_0,    KC_MINS, KC_NA, KC_NA,   KC_NA,   KC_NP,   KC_NP
  ),
  [NSSL] = LAYOUT_miryoku(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, KC_NA,   KC_NA,   KC_NA,   KC_NA,   KC_RST,
    KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS, KC_NA,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, KC_NA,   KC_NA,   KC_NA,   KC_ALGR, KC_NA,
    KC_NP,   KC_NP,   KC_GT,   KC_RPRN, KC_UNDS, KC_NA,   KC_NA,   KC_NA,   KC_NP,   KC_NP
  )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

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
