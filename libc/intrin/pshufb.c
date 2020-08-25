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
#include "libc/intrin/pshufb.h"
#include "libc/str/str.h"

/**
 * Shuffles and/or clears 8-bit integers.
 *
 * @param 𝑎 [w/o] receives result
 * @param 𝑏 [r/o] supplies byte vector
 * @param 𝑐 [r/o] supplies mask vector
 * @note goes fast w/ ssse3 (intel c. 2004, amd c. 2011)
 * @note doesn't perfectly emulate mmx
 * @mayalias
 */
void(pshufb)(uint8_t a[16], const uint8_t b[16], const uint8_t c[16]) {
  unsigned i;
  uint8_t r[16];
  for (i = 0; i < 16; ++i) r[i] = (c[i] & 0x80) ? 0 : b[c[i] & 0x0F];
  memcpy(a, r, 16);
}
