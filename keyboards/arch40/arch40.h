#pragma once

#include "quantum.h"
#include "rev1.h"

#define ___ KC_NO

/* PCB matrix layout
 *       .----------------------------------------------------------------.
 *       | 00 | 01 | 02 | 03 | 04 | 05 |    | 07 | 08 | 09 | 0A | 0B | 0C |
 *       |-----------------------------------------------------------|----|
 *       | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A | 1B | 1C |
 *       |-----------------------------------------------------------|----|
 *       | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 2A | 2B | 2C |
 *       |-----------------------------------------------------------|----|
 *       | 30 |    | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 3A |    | 3C |
 *       `----------------------------------------------------------------`
 *
 * physical layout
 *         .-----------------------------..-----------------------------.
 *        / 00 / 01 / 02 / 03 / 04 / 05 /  \ 07 \ 08 \ 09 \ 0A \ 0B \ 0C \
 *       /-----------------------------/    \------------------------\----\
 *      / 10 / 11 / 12 / 13 / 14 / 15 /      \ 17 \ 18 \ 19 \ 1A \ 1B \ 1C \
 *     /-----------------------------/        \------------------------\----\
 *    / 20 / 21 / 22 / 23 / 24 / 25 /          \ 27 \ 28 \ 29 \ 2A \ 2B \ 2C \
 *   /-----------------------------/            \------------------------\----\
 *  / 30 /    / 32 / 33 / 34 / 35 /              \ 37 \ 38 \ 39 \ 3A \    \ 3C \
 * `-----------------------------/----.      .----\-----------------------------`
 *                           |   36   |      | 26 | 16 |
 *                           `--------`      `----`----`
 */

#define LAYOUT( \
   k00, k01, k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
   k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3c  \
) \
{ \
  {k00, k01, k02, k03, k04, k05, ___, k07, k08, k09, k0a, k0b, k0c}, \
  {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c}, \
  {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c}, \
  {k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, ___, k3c}  \
}
