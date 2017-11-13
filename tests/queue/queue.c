/*
 * Copyright (C) 2016 - 2017  Sören Brinkmann <soeren.brinkmann@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */
#include <errno.h>
#include <foo.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	void *data;
	void *queue = NULL;

	/* peek without queue */
	data = foo_queue_peek(queue);
	if (data != NULL) {
		printf("ERROR: data != NULL\n");
		return 200;
	}

	/* create queue */
	queue = foo_queue_create();
	if (!queue) {
		printf("ERROR: queue creation failed\n");
		return 201;
	}

	/* peek created but empty queue */
	data = foo_queue_peek(queue);
	if (data != NULL) {
		printf("ERROR: data != NULL\n");
		return 202;
	}

	for (size_t i = 0; i < 1000; i++) {
		/* enqueue data */
		int ret = foo_queue_enqueue(queue, (void *)i);
		if (ret) {
			printf("ERROR: enqueue failed (%d)\n", ret);
			return ret;
		}

		/* peek queue */
		data = foo_queue_peek(queue);
		if (data != (void *)0) {
			printf("ERROR: data != %zu (%zu)\n", i, (size_t)data);
			return 203;
		}
	}

	for (size_t i = 0; i < 111; i++) {
		/* dequeue data */
		size_t data = (size_t)foo_queue_dequeue(queue);
		if (data != i) {
			printf("ERROR: data != %zu (%zu)\n", i, (size_t)data);
			return 204;
		}
	}

	/* destroy queue */
	foo_queue_destroy(queue);

	printf("tests pass\n");

	return 0;
}
