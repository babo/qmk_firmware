AUDIO_ENABLE = no          # Audio output on port C6
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality on B7 by default
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
BOOTLOADER = atmel-dfu
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration
COMMAND_ENABLE = no        # Commands for debug and configuration
CONSOLE_ENABLE = yes       # Console for debug
ENCODER_ENABLE = no        # Enables the use of one or more encoders
EXTRAKEY_ENABLE = yes      # Audio control and System control
FAUXCLICKY_ENABLE = no     # Use buzzer to emulate clicky switches
HD44780_ENABLE = no        # Enable support for HD44780 based LCDs
LTO_ENABLE = yes		   # Enable link type optimization
MIDI_ENABLE = no           # MIDI support
MOUSEKEY_ENABLE = yes      # Mouse keys
NKRO_ENABLE = yes          # USB Nkey Rollover
OLED_DRIVER_ENABLE = yes    # Enables the use of OLED displays
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
RGBLIGHT_STARTUP_ANIMATION = yes
UNICODE_ENABLE = yes       # Unicode
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
