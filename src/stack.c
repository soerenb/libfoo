/*
 * stack.c
 * Copyright (C) 2016  Sören Brinkmann <soeren.brinkmann@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <errno.h>
#include <stdlib.h>

struct foo_stack_item {
	struct foo_stack_item *next;
	void *data;
};

void *foo_stack_create(void)
{
	struct foo_stack_item **stack = calloc(1, sizeof(*stack));

	return stack;
}

void foo_stack_destroy(void *_stack)
{
	struct foo_stack_item *tmp1;
	struct foo_stack_item **stackp = _stack;

	if (__builtin_expect(!stackp, 0))
		return;

	tmp1 = *stackp;
	*stackp = NULL;
	while (tmp1) {
		struct foo_stack_item *tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}

	free(stackp);
}

int foo_stack_push(void *_stack, void *data)
{
	struct foo_stack_item *e;
	struct foo_stack_item **stackp = _stack;

	if (__builtin_expect(!stackp, 0))
		return EINVAL;

	e = calloc(1, sizeof(*e));
	if (__builtin_expect(!e, 0))
		return ENOMEM;

	e->data = data;
	e->next = *stackp;
	*stackp = e;

	return 0;
}

void *foo_stack_pop(void *_stack)
{
	void *data;
	struct foo_stack_item *e;
	struct foo_stack_item **stackp = _stack;

	if (__builtin_expect(!stackp || !(*stackp), 0))
		return NULL;

	e = *stackp;
	data = e->data;
	*stackp = e->next;
	free(e);

	return data;
}

void *foo_stack_peek(void *_stack)
{
	struct foo_stack_item **stackp = _stack;

	if (__builtin_expect(!stackp || !(*stackp), 0))
		return NULL;

	return (*stackp)->data;
}
