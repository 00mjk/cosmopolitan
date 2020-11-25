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

static void critbit0_clear_traverse(void *top) {
  unsigned char *p = top;
  if (1 & (intptr_t)p) {
    struct CritbitNode *q = (void *)(p - 1);
    critbit0_clear_traverse(q->child[0]);
    critbit0_clear_traverse(q->child[1]);
    free(q), q = NULL;
  } else {
    free(p), p = NULL;
  }
}

/**
 * Removes all items from 𝑡.
 * @param t tree
 * @note h/t djb and agl
 */
void critbit0_clear(struct critbit0 *t) {
  if (t->root) {
    critbit0_clear_traverse(t->root);
    t->root = NULL;
  }
  t->count = 0;
}
