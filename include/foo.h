#ifndef __LIBFOO_H__
#define __LIBFOO_H__

#include <stdio.h>

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))

int foo_chkadd(int a, int b);
unsigned int foo_chkuadd(unsigned int a, unsigned int b);
char *foo_gets(void);
long foo_filesize(FILE *fd);

#endif
