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
#include "libc/assert.h"
#include "libc/intrin/palignr.h"
#include "libc/macros.h"

/**
 * Overlaps vectors.
 *
 *     𝑖= 0 means 𝑐←𝑎
 *   0<𝑖<16 means 𝑐←𝑎║𝑏
 *     𝑖=16 means 𝑐←𝑏
 *  16<𝑖<32 means 𝑐←𝑏║0
 *     𝑖≥32 means 𝑐←0
 *
 * @param 𝑖 goes faster as constexpr
 * @note not compatible with mmx
 * @see pvalignr()
 * @mayalias
 */
void(palignr)(void *c, const void *b, const void *a, unsigned long i) {
  char t[48];
  memcpy(t, a, 16);
  memcpy(t + 16, b, 16);
  memset(t + 32, 0, 16);
  memcpy(c, t + MIN(i, 32), 16);
}
