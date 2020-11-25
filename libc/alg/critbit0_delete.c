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
#include "libc/alg/critbit0.h"
#include "libc/alg/internal.h"
#include "libc/mem/mem.h"
#include "libc/str/str.h"

/**
 * Removes 𝑢 from 𝑡.
 * @param t tree
 * @param u NUL-terminated string
 * @return true if 𝑡 was mutated
 * @note h/t djb and agl
 */
bool critbit0_delete(struct critbit0 *t, const char *u) {
  const unsigned char *ubytes = (void *)u;
  const size_t ulen = strlen(u);
  unsigned char *p = t->root;
  void **wherep = &t->root;
  void **whereq = 0;
  struct CritbitNode *q = 0;
  int direction = 0;
  if (!p) return false;
  while (1 & (intptr_t)p) {
    whereq = wherep;
    q = (void *)(p - 1);
    unsigned char c = 0;
    if (q->byte < ulen) c = ubytes[q->byte];
    direction = (1 + (q->otherbits | c)) >> 8;
    wherep = q->child + direction;
    p = *wherep;
  }
  if (0 != strcmp(u, (const char *)p)) return false;
  free(p), p = NULL;
  if (!whereq) {
    t->root = NULL;
    t->count = 0;
    return true;
  }
  *whereq = q->child[1 - direction];
  free(q), q = NULL;
  t->count--;
  return true;
}
