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
	void *queue = NULL;

	/* peek without queue */
	data = foo_queue_peek(queue);
	if (data != NULL) {
		cout << "ERROR: data != NULL\n";
		return 200;
	}

	/* create queue */
	queue = foo_queue_create();
	if (!queue) {
		cout << "ERROR: queue creation failed\n";
		return 201;
	}

	/* peek created but empty queue */
	data = foo_queue_peek(queue);
	if (data != NULL) {
		cout << "ERROR: data != NULL\n";
		return 202;
	}

	for (size_t i = 0; i < 1000; i++) {
		/* enqueue data */
		int ret = foo_queue_enqueue(queue, (void *)i);
		if (ret) {
			cout << "ERROR: enqueue failed (" << ret << ")\n";
			return ret;
		}

		/* peek queue */
		data = foo_queue_peek(queue);
		if (data != (void *)0) {
			cout << "ERROR: data != " << i << " (" << data << ")\n";
			return 203;
		}
	}

	for (size_t i = 0; i < 111; i++) {
		/* dequeue data */
		size_t data = (size_t)foo_queue_dequeue(queue);
		if (data != i) {
			cout << "ERROR: data != " << i << " (" << data << ")\n";
			return 204;
		}
	}

	/* destroy queue */
	foo_queue_destroy(queue);

	cout << "tests pass\n";

	return 0;
}
