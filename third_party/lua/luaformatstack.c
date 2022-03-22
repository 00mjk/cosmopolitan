/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2022 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/stdio/append.internal.h"
#include "third_party/lua/cosmo.h"

dontdiscard char *LuaFormatStack(lua_State *L) {
  int i, top;
  char *b = 0;
  top = lua_gettop(L);
  for (i = 1; i <= top; i++) {
    if (i > 1) appendw(&b, '\n');
    appendf(&b, "\t%d\t%s\t", i, luaL_typename(L, i));
    switch (lua_type(L, i)) {
      case LUA_TNUMBER:
        appendf(&b, "%g", lua_tonumber(L, i));
        break;
      case LUA_TSTRING:
        appends(&b, lua_tostring(L, i));
        break;
      case LUA_TBOOLEAN:
        appends(&b, lua_toboolean(L, i) ? "true" : "false");
        break;
      case LUA_TNIL:
        appends(&b, "nil");
        break;
      default:
        appendf(&b, "%p", lua_topointer(L, i));
        break;
    }
  }
  return b;
}
