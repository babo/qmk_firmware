/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// default but important
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

#define RETRO_TAPPING

#define LAYOUT_miryoku( \
       K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09, \
       K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19, \
       K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29, \
       N30,   N31,   K32,   K33,   K34,   K35,   K36,   K37,   N38,   N39 \
) \
LAYOUT_gergo( \
ODI,      K00,    K01,    K02,   K03,   K04,                                  K05,   K06,   K07,   K08,   K09,   UDI, \
KC_LSFT,  K10,    K11,    K12,   K13,   K14,   EAC,                     IAC,  K15,   K16,   K17,   K18,   K19,   KC_RSFT, \
ODA,      K20,    K21,    K22,   K23,   K24,   AAC, OAC,      UAC,    OAC,  K25,   K26,   K27,   K28,   K29,   UDA, \
                            K32,   K33,   K34,   K32,                       K35,    K35,   K36,   K37   \
)
