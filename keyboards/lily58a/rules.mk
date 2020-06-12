# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

DEFAULT_FOLDER = lily58a/rev1

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
AUDIO_ENABLE = no           # Audio output on port C6
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
COMMAND_ENABLE = no         # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug(+400)
EXTRAKEY_ENABLE = no        # Audio control and System control(+450)
MIDI_ENABLE = no            # MIDI controls
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
OLED_DRIVER_ENABLE = no     # OLED display
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
SPLIT_KEYBOARD = yes        # Use split_common libraries
TAP_DANCE_ENABLE = no       # Enable tapdance
UNICODE_ENABLE = no         # Unicode

# if firmware size over limit, try this option
# CFLAGS += -flto
