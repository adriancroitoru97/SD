#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t *
st_create(unsigned int data_size)
{
	stack_t *stack = malloc(sizeof(*stack));
	DIE(!stack, "malloc error");

	stack->list = ll_create(data_size);

	return stack;
}

unsigned int
st_get_size(stack_t *st)
{
	if (!st || !st->list)
		return 0;

	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st)
{
	//return !st || !st->list || !st->list->size;
	if (!st || !st->list || !st->list->size)
		return 1;

	return 0;
}

void *
st_peek(stack_t *st)
{
	if (!st || !st->list || st->list->size == 0)
		return NULL;

	return st->list->head->data;
}

void
st_pop(stack_t *st)
{
	if (!st || !st->list)
		return;

	ll_node_t *removed = ll_remove_nth_node(st->list, 0);
	free(removed->data);
	free(removed);
}

void
st_push(stack_t *st, void *new_data)
{
	if (!st || !st->list)
		return;

	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st)
{
	if (!st || !st->list)
		return;

	ll_free(&st->list);
}

void
st_free(stack_t *st)
{
	if (!st || !st->list)
		return;

	ll_free(&st->list);
	free(st);
}
