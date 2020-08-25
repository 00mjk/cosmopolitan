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
#include "libc/intrin/punpckhdq.h"

/**
 * Interleaves high doublewords.
 *
 *          0    1    2    3
 *       B  aaaa bbbb CCCC DDDD
 *       C  eeee ffff GGGG HHHH
 *                    └┬─┘ └─┬┘
 *                ┌────┘     │
 *          ┌─────┴─┐ ┌──────┴┐
 *     → A  CCCC GGGG DDDD HHHH
 *
 * @param 𝑎 [w/o] receives reduced 𝑏 and 𝑐 interleaved
 * @param 𝑏 [r/o] supplies four doublewords
 * @param 𝑐 [r/o] supplies four doublewords
 * @mayalias
 */
void(punpckhdq)(uint32_t a[4], const uint32_t b[4], const uint32_t c[4]) {
  a[0] = b[2];
  a[1] = c[2];
  a[2] = b[3];
  a[3] = c[3];
}
