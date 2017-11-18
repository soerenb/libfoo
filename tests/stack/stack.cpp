/*
 * Copyright (C) 2016 - 2017  Sören Brinkmann <soeren.brinkmann@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */
#include <errno.h>
#include <foo.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	void *data;
	void *stack = NULL;

	/* peek without stack */
	data = foo_stack_peek(stack);
	if (data != NULL) {
		cout << "ERROR: data != NULL\n";
		return 200;
	}

	/* create stack */
	stack = foo_stack_create();
	if (!stack) {
		cout << "ERROR: stack creation failed\n";
		return 201;
	}

	/* peek created but empty stack */
	data = foo_stack_peek(stack);
	if (data != NULL) {
		cout << "ERROR: data != NULL\n";
		return 202;
	}

	for (size_t i = 0; i < 1000; i++) {
		/* push data onto stack */
		int ret = foo_stack_push(stack, (void *)i);
		if (ret) {
			cout << "ERROR: push failed (" << ret << ")\n";
			return ret;
		}

		/* peek stack */
		data = foo_stack_peek(stack);
		if (data != (void *)i) {
			cout << "ERROR: data != " << i << " (" << data << ")\n";
			return 203;
		}
	}

	for (size_t i = 0; i < 111; i++) {
		/* pop data from stack */
		size_t data = (size_t)foo_stack_pop(stack);
		if (data != 1000 - 1 - i) {
			cout << "ERROR: data != " << 1000 - 1 - i << " (" << data << ")\n";
			return 204;
		}
	}

	/* destroy stack */
	foo_stack_destroy(stack);

	cout << "tests pass\n";

	return 0;
}
