/*
 * chkuadd.c
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
#include <limits.h>

/* foo_chkuadd() - Test unsinged addition for unsinged int overflow
 * @a First summand
 * @b Second summand
 * Returns UINT_MAX in case of an overflow, @a + @b otherwise
 */
unsigned int foo_chkuadd(unsigned int a, unsigned int b)
{
	if (UINT_MAX - b < a) {
		fputs("unsigned int overflow\n", stderr);
		return UINT_MAX;
	}
	return (a + b);
}
