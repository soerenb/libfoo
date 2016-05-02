/*
 * queue.c
 * Copyright (C) 2016  Sören Brinkmann <soeren.brinkmann@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */
#include <errno.h>
#include <stdlib.h>

struct foo_queue {
	struct foo_q_item *head;
	struct foo_q_item *tail;
};

struct foo_q_item {
	struct foo_q_item *next;
	void *data;
};

void *foo_queue_create(void)
{
	struct foo_queue *queue = calloc(1, sizeof(*queue));

	return queue;
}

void foo_queue_destroy(void *_queue)
{
	struct foo_q_item *tmp1;
	struct foo_queue *queue = _queue;

	if (__builtin_expect(!queue, 0))
		return;

	tmp1 = queue->head;
	while (tmp1) {
		struct foo_q_item *tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}

	free(queue);
}

int foo_queue_enqueue(void *_queue, void *data)
{
	struct foo_q_item *e;
	struct foo_queue *queue = _queue;

	if (__builtin_expect(!queue, 0))
		return EINVAL;

	e = calloc(1, sizeof(*e));
	if (__builtin_expect(!e, 0))
		return ENOMEM;

	e->data = data;

	/* empty queue */
	if (__builtin_expect(!queue->tail, 0))
		queue->head = e;
	else
		queue->tail->next = e;

	queue->tail = e;

	return 0;
}

void *foo_queue_dequeue(void *_queue)
{
	void *data;
	struct foo_q_item *e;
	struct foo_queue *queue = _queue;

	if (__builtin_expect(!queue || !queue->head, 0))
		return NULL;

	e = queue->head;
	queue->head = e->next;
	data = e->data;
	free(e);

	if (__builtin_expect(!queue->head, 0))
		queue->tail = NULL;

	return data;
}

void *foo_queue_peek(void *_queue)
{
	struct foo_queue *queue = _queue;

	if (__builtin_expect(!queue || !queue->head, 0))
		return NULL;

	return queue->head->data;
}
