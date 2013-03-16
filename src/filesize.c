/*
 * filesize.c
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

/**
 * foo_filesize() - Get filesize
 * @fd	File descriptor
 * Returns the size of file 'fd' in bytes
 */
long foo_filesize(FILE *fd)
{
	long size;
	long fpi = ftell(fd);

	fseek(fd, 0L, SEEK_END);
	size = ftell(fd);
	fseek(fd, fpi, SEEK_SET);

	return size;
}
