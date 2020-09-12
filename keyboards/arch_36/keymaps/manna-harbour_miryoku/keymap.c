#include QMK_KEYBOARD_H
#include "split_util.h"

#include "manna-harbour_miryoku.h"
#include "babo.h"

uint8_t is_master;
uint16_t rgb_edit_timer = 0;
uint16_t last_rgb_char = 0;

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
        case RGB_MOD:
        case RGB_HUD:
        case RGB_HUI:
        case RGB_SAD:
        case RGB_SAI:
        case RGB_VAI:
        case RGB_VAD:
            rgb_edit_timer = timer_read();
            last_rgb_char = keycode;
            return true;
    }

    return true;
}

#ifdef OLED_DRIVER_ENABLE

#define ANIM_NUM_FRAMES 4
#define ANIM_FRAME_DURATION 100

#ifdef ANIM_REVERSE
#define ANIM_TOTAL_FRAMES (2*((ANIM_NUM_FRAMES)-1))
#else
#define ANIM_TOTAL_FRAMES ANIM_NUM_FRAMES
#endif

uint16_t anim_timer = 0;
uint8_t current_anim_frame = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layout: Colemak DH"), false);
}

#ifdef RGBLIGHT_ENABLE
bool cleared = false;
void render_rgb_state(void) {
    if(!rgblight_get_mode()) {
        if(!cleared) {
            oled_clear();
            cleared = true;
        }
        return;
    }
    cleared = false;
    uint8_t width = (OLED_DISPLAY_WIDTH/OLED_FONT_WIDTH)-10;
    uint8_t hue = (rgblight_get_hue()*width/255),
        sat = (rgblight_get_sat()*width/255),
        val = (rgblight_get_val()*width/255);
    bool changing_hue = timer_elapsed(rgb_edit_timer) < 1000 && (last_rgb_char == RGB_HUI || last_rgb_char == RGB_HUD);
    bool changing_sat =  timer_elapsed(rgb_edit_timer) < 1000 && (last_rgb_char == RGB_SAI || last_rgb_char == RGB_SAD);
    bool changing_val =  timer_elapsed(rgb_edit_timer) < 1000 && (last_rgb_char == RGB_VAI || last_rgb_char == RGB_VAD);

    uint8_t i;

    oled_write_ln_P(PSTR(""), false);

    oled_write_P(PSTR("Hue:    ["), changing_hue);
    for(i = 0; i < width; ++i) {
        oled_write_P(i<hue?PSTR("-"):i==hue?PSTR("|"):PSTR(" "), changing_hue);
    }
    oled_write_P(PSTR("]"), changing_hue);
    oled_write_P(PSTR("Sat:    ["), changing_sat);
    for(i = 0; i < width; ++i) {
        oled_write_P(i<sat?PSTR("-"):i==sat?PSTR("|"):PSTR(" "), changing_sat);
    }
    oled_write_P(PSTR("]"), changing_sat);
    oled_write_P(PSTR("Bri:    ["), changing_val);
    for(i = 0; i < width; ++i) {
        oled_write_P(i<val?PSTR("-"):i==val?PSTR("|"):PSTR(" "), changing_val);
    }
    oled_write_P(PSTR("]"), changing_val);
}
#endif // RGBLIGHT_ENABLE

void render_layer_state(void) {
    oled_write_P(PSTR("Layer:  "), false);
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case MBO:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case MEDR:
            oled_write_ln_P(PSTR("Media"), false);
            break;
        case NAVR:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case MOUR:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case NSL:
            oled_write_ln_P(PSTR("Number"), false);
            break;
        case NSSL:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case FUNL:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unknown"), false);
    }
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("Lock:   "), false);
    oled_write_P(PSTR("123"), led_state.num_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(led_state.caps_lock?PSTR("ABC"):PSTR("abc"), led_state.caps_lock);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:   "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("W"), (modifiers & MOD_MASK_GUI));
}

static void render_status(void) {
    // Host Keyboard Layer Status
    render_default_layer_state();
    render_layer_state();
    render_keylock_status(host_keyboard_led_state());
    render_mod_status(get_mods() | get_oneshot_mods());
#ifdef RGBLIGHT_ENABLE
    render_rgb_state();
#endif // RGBLIGHT_ENABLE
}

void oled_task_user(void) {
    if (isLeftHand) {
        render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    }
}
#endif
