/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ This program is free software; you can redistribute it and/or modify         │
│ it under the terms of the GNU General Public License as published by         │
│ the Free Software Foundation; version 2 of the License.                      │
│                                                                              │
│ This program is distributed in the hope that it will be useful, but          │
│ WITHOUT ANY WARRANTY; without even the implied warranty of                   │
│ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU             │
│ General Public License for more details.                                     │
│                                                                              │
│ You should have received a copy of the GNU General Public License            │
│ along with this program; if not, write to the Free Software                  │
│ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA                │
│ 02110-1301 USA                                                               │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "dsp/core/q.h"
#include "libc/assert.h"
#include "libc/dce.h"
#include "libc/limits.h"
#include "libc/macros.h"
#include "libc/math.h"
#include "libc/str/str.h"

/**
 * Precomputes integers that can replace floating-point operands.
 *
 *    “G-d made the integers, all else is the work of man.
 *                               — Leopold Kronecker
 *
 * This function shifts the decimal point to the left:
 *
 *     𝑛ᵢ ← ROUND[𝑐ᵢ × 2ᵐ] + φᵢ
 *
 * With extra effort to compute φ which is normally all zeroes but gives
 * us better rounding when it isn't. It's assumed optimized coefficients
 * will be used like this:
 *
 *     (Σᵢ𝑥ᵢ𝑛ᵢ + 2⁽ᵐ⁻¹⁾) / 2ᵐ            where 𝑥∈[𝐿,𝐻] and 𝑖∈[0,6)
 *
 * Intended to compute this
 *
 *     ROUND[Σᵢ𝑥ᵢ𝑐ᵢ]
 *
 * As accurately or approximately as you want it to be. Popular scaling
 * factors are 7, 15, 16, 22, and 31. Building this code under MODE=tiny
 * will DCE the math.
 *
 * @param N receives optimized integers
 * @param C provides ideal coefficients
 * @param M is log₂ scaling factor, e.g. 7
 * @param L is minimum input data size, e.g. 0
 * @param H is maximum input data size, e.g. 255
 * @return sum of errors for all inputs
 * @see en.wikipedia.org/wiki/Binary_scaling
 * @see o/tool/build/coefficients.com
 * @cost ~300ns
 */
long GetIntegerCoefficients(long N[static 6], const double C[static 6], long M,
                            long L, long H) {
  int i;
  int j[6], J[6];
  int O[6] = {0};
  int S[3] = {0, -1, +1};
  double R[6], K[6], D[6], HM, HL, least, error;
  least = 1;
  HM = 1L << M;
  HL = H - L + 1;
  assert(H >= L);
  assert(HL <= HM);
  for (i = 0; i < 6; ++i) {
    least *= HL;
    if (fabs(C[i]) > DBL_MIN) {
      J[i] = ARRAYLEN(S);
      R[i] = C[i] * HM;
      K[i] = rint(R[i]);
      N[i] = K[i];
    } else {
      J[i] = 1;
      R[i] = 0;
      K[i] = 0;
      N[i] = 0;
    }
  }
  if (!NoDebug() && least > 1) {
    for (j[0] = 0; j[0] < J[0]; ++j[0]) {
      for (j[1] = 0; j[1] < J[1]; ++j[1]) {
        for (j[2] = 0; j[2] < J[2]; ++j[2]) {
          for (j[3] = 0; j[3] < J[3]; ++j[3]) {
            for (j[4] = 0; j[4] < J[4]; ++j[4]) {
              for (j[5] = 0; j[5] < J[5]; ++j[5]) {
                for (i = 0; i < ARRAYLEN(J); ++i) {
                  D[i] = S[j[i]] + K[i] - R[i];
                }
                if ((error = DifferSumSq(D, L, H) / HM) < least) {
                  least = error;
                  memcpy(O, j, sizeof(j));
                }
              }
            }
          }
        }
      }
    }
    for (i = 0; i < 6; ++i) {
      N[i] += S[O[i]];
    }
  }
  return lround(least);
}
