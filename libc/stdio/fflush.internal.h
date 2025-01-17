#ifndef COSMOPOLITAN_LIBC_STDIO_FFLUSH_H_
#define COSMOPOLITAN_LIBC_STDIO_FFLUSH_H_
#include "libc/stdio/stdio.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

struct StdioFlushHandles {
  size_t i, n;
  FILE **p;
};

struct StdioFlush {
  int lock;
  struct StdioFlushHandles handles;
  FILE *handles_initmem[8];
};

hidden extern struct StdioFlush __fflush;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_STDIO_FFLUSH_H_ */
