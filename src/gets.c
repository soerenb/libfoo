/*
 * gets.c
 * Copyright (C) 2013  Sören Brinkmann <soeren.brinkmann@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 80

/**
 * foo_gets() - Read a line from stdin
 * Returns a pointer to the read input line or NULL if nothing read or an error
 * occurred. The returned object has to be freed by the caller.
 */
char *foo_gets(void)
{
	char *ch;
	char buf[BUFSIZE];
	size_t len;
	size_t strlen;
	int loop = 1;
	char *string = NULL;
	size_t size = BUFSIZE;

	while (loop) {
		ch = fgets(buf, BUFSIZE, stdin);
		if (ch == NULL)
			return NULL;
		
		len = 1;
		while (*ch != '\0') {
			if (*ch == '\n')
				loop = 0;
			len++;
			ch++;
		}
		if (string) {
			char *tmp;
			size += BUFSIZE - 1;
			tmp = malloc(size);
			memcpy(tmp, string, strlen - 1);
			memcpy(tmp + strlen - 1, buf, len);
			strlen += len - 1;
			free(string);
			string = tmp;
		} else {
			string = malloc(len);
			strlen = len;
			memcpy(string, buf, len);
		}
	}
	return string;
}
