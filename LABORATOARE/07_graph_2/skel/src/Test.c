#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
static void
dfs_connected_comps(
	list_graph_t *lg,
	int node,
	int *visited,
	linked_list_t *component
) {
	stack_t *stack = st_create(sizeof(int));

	visited[node] = 1;
	ll_add_nth_node(component, component->size, &node);

	st_push(stack, &node);

	while(!st_is_empty(stack))
	{
		int val = *((int *)st_peek(stack));
		ll_node_t *node_now = lg->neighbors[val]->head;

		int cnt = 0;
		while(node_now)
		{
			int v = *((int*)(node_now->data));
			if(visited[v] == 0)
			{
				visited[v] = 1;
				ll_add_nth_node(component, component->size, &v);
				st_push(stack, &v);
				cnt = 1;
				break;
			}

			node_now = node_now->next;
		}

		if(cnt == 0)
		{
			visited[val] = 1;
			st_pop(stack);
		}
	}

	st_free(stack);
}

static linked_list_t **
connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	DIE(!comps, "malloc comps failed");

	*num_comp = 0;
	for(int i = 0; i < lg->nodes; i++)
	{
		if(visited[i] == 0)
		{
			comps[*num_comp] = ll_create(sizeof(int));
			dfs_connected_comps(lg, i, visited, comps[*num_comp]);
			*num_comp = *num_comp + 1;
		}
	}

	return comps;
}

static void
dfs_topo_sort(list_graph_t *lg, int node, int *visited, linked_list_t *sorted)
{
	stack_t *stack = st_create(sizeof(int));
	
	int time_cnt = 0;
	time_cnt++;
	visited[node] = 1;

	st_push(stack, &node);

	while(st_is_empty(stack) != 1)
	{
		int val = *(int *)(st_peek(stack));
		ll_node_t *node_now = lg->neighbors[val]->head;

		int contor = 0;

		while(node_now)
		{
			int v = *(int*)(node_now->data);

			if(visited[v] == 0)
			{
				time_cnt++;
				visited[v] = 1;
				st_push(stack, &v);
				contor = 1;
				break;
			}
			node_now = node_now->next;
		}

		if(contor == 0)
			{
				time_cnt++;
				ll_add_nth_node(sorted, 0, &val);
				visited[val] = -1;
				st_pop(stack);
			}
	}

	st_free(stack);
}

static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));
	
	for (int i = 0; i < lg->nodes; i++) {
		if (visited[i] == 0) {
			dfs_topo_sort(lg, i, visited, sorted);
		}
	}

	return sorted;
}

static void
test_connected_comp(void)
{
	unsigned int num_comps, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("UNDIRECTED graph for the connected components problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("Found %d connected components:\n", num_comps);
	for (i = 0; i != num_comps; ++i) {
		ll_print_int(comps[i]);
		ll_free(comps + i);
	}
	printf("\n");

	free(comps);
	lg_free(lg);
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

int
main(void)
{
	/* Ex 1 */
	test_connected_comp();

	/* Ex 2 */
	test_topo_sort();

	return 0;
}
