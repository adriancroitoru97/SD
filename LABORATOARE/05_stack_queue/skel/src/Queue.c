#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *queue = malloc(sizeof(*queue));
	DIE(!queue, "malloc error");

	queue->max_size = max_size;
	queue->size = 0;
	queue->data_size = data_size;
	queue->read_idx = 0;
	queue->write_idx = 0;
	queue->buff = malloc(max_size * sizeof(*queue->buff));

	return queue;
}

unsigned int
q_get_size(queue_t *q)
{
	if (!q)
		return 0;

	return(q->size);
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	if (!q)
		return 1;

	if (q->size == 0)
		return 1;

	return 0;
}

void *
q_front(queue_t *q)
{
	if (!q)
		return NULL;

	return(q->buff[q->read_idx]);
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	if (!q || q->size == 0)
		return false;

	free(q->buff[q->read_idx]);
	
	q->read_idx++;
	q->read_idx = q->read_idx % q->max_size;
	q->size--;

	return true;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	if (!q)
		return false;

	if (q->size >= q->max_size)
		return false;

	void *data_copy = malloc(q->data_size);
	DIE(!data_copy, "malloc error");
	memcpy(data_copy, new_data, sizeof(q->data_size));
	q->buff[q->write_idx] = data_copy;

	q->size++;
	q->write_idx++;
	q->write_idx = q->write_idx % q->max_size;

	return true;
}

void
q_clear(queue_t *q)
{	
	if (!q)
		return;

	for (unsigned int i = q->read_idx; i != q->write_idx; i = (i + 1) % q->max_size)
		free(q->buff[i]);

	q->size = 0;
	q->read_idx = 0;
	q->write_idx = 0;
}

void
q_free(queue_t *q)
{
	if (!q)
		return;

	q_clear(q);
	free(q->buff);
	free(q);
}
