#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "utils.h"

list_graph_t*
lg_create(int nodes)
{
	list_graph_t* graph = malloc(sizeof(*graph));
	DIE(!graph, "malloc error");

	graph->neighbors = calloc(nodes, sizeof(linked_list_t));
	DIE(!graph->neighbors, "calloc error");
	for (int i = 0; i < nodes; i++) {
		graph->neighbors[i] = ll_create(sizeof(int));
		DIE(!graph->neighbors[i], "calloc error");
	}

	graph->nodes = nodes;

	return graph;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	if (!graph || !graph->neighbors)
		return;

	ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, (void*) &dest);
}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	if (!graph || !graph->neighbors)
		return 0;

	ll_node_t* node = graph->neighbors[src]->head;

	while (node) {
		if (*(int*)node->data == dest)
			return 1;

		node = node->next;
	}

	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	if (!graph || !graph->neighbors)
		return NULL;

	return graph->neighbors[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	if (!graph || !graph->neighbors)
		return;

	ll_node_t* node = graph->neighbors[src]->head;
	ll_node_t* removed;
	unsigned int cnt = 0;

	while (node) {
		if (*(int*)node->data == dest) {
			removed = ll_remove_nth_node(graph->neighbors[src], cnt);
			free(removed->data);
			free(removed);
			break;
		}

		cnt++;
		node = node->next;
	}
}

void
lg_free(list_graph_t* graph)
{
	if (!graph || !graph->neighbors)
		return;

	for (int i = 0; i < graph->nodes; i++)
		ll_free(&graph->neighbors[i]);

	free(graph->neighbors);
	free(graph);
}