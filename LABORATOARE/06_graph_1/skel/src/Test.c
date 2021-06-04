#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "utils.h"
#include "Queue.h"

#define MAX_NODES 10
#define MAX_INT 99999999

void
print_matrix_graph(matrix_graph_t* mg)
{
	if (!mg || !mg->matrix)
		return;

	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++) {
			printf("%d ", mg->matrix[i][j]);
		}
		printf("\n");
	}
}

void
print_list_graph(list_graph_t* lg)
{
	if (!lg || !lg->neighbors)
		return;

	for (int i = 0; i < lg->nodes; i++) {
		printf("%d: ", i);
		ll_print_int(lg->neighbors[i]);
	}
}

void
bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent)
{
	int *d = malloc(lg->nodes * sizeof(int));
	for (int i = 0; i < lg->nodes; i++) {
		color[i] = 0;
		parent[i] = 0;
		d[i] = MAX_INT;
	}

	color[node] = 1;
	d[node] = 0;

	queue_t *q = q_create(sizeof(int), lg->nodes);
	q_enqueue(q, &node);

	while (!q_is_empty(q)) {
		int v = *(int*)(q_front(q));
		q_dequeue(q);

		ll_node_t* current = lg->neighbors[v]->head;
		while (current) {
			int u = *(int*)(current->data);
			if (color[u] == 0) {
				color[u] = 1;
				parent[u] = v;
				d[u] = d[v] + 1;
				q_enqueue(q, &u);
				printf("%d ", u);
			}
			current = current->next;
		}

		printf("\n");
		color[v] = 2;
	}

	q_free(q);
	free(d);
}

void
floyd_warshall(matrix_graph_t* mg)
{
    int dist[mg->nodes][mg->nodes];
 
    for (int i = 0; i < mg->nodes; i++)
        for (int j = 0; j < mg->nodes; j++)
            dist[i][j] = mg->matrix[i][j];

    for (int k = 0; k < mg->nodes; k++)
    {
        for (int i = 0; i < mg->nodes; i++)
        {
            for (int j = 0; j < mg->nodes; j++)
            {
                if (dist[k][j] != 0 && dist[i][k] != 0 && i != j &&
                	(dist[i][j] != 0 || dist[i][k] + dist[k][j] < dist[i][j]))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 
    for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++) {
			printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
}

int
main()
{
	//int nodes, edges;
	int x[MAX_NODES], y[MAX_NODES];
	//int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("\n---TEST PRINT MATRIX GRAPH---\n");
	print_matrix_graph(mg);
	printf("\n---TEST PRINT LIST GRAPH---\n");
	print_list_graph(lg);

	printf("\n---TEST BFS LIST GRAPH---\n");
	list_graph_t *lg_bfs = lg_create(MAX_NODES);
    lg_add_edge(lg_bfs, numbers[1], numbers[2]);
    lg_add_edge(lg_bfs, numbers[1], numbers[3]);
    lg_add_edge(lg_bfs, numbers[1], numbers[4]);
    lg_add_edge(lg_bfs, numbers[2], numbers[5]);
    lg_add_edge(lg_bfs, numbers[2], numbers[3]);
    lg_add_edge(lg_bfs, numbers[2], numbers[1]);
    lg_add_edge(lg_bfs, numbers[3], numbers[2]);
    lg_add_edge(lg_bfs, numbers[3], numbers[6]);
    lg_add_edge(lg_bfs, numbers[3], numbers[7]);
    lg_add_edge(lg_bfs, numbers[4], numbers[1]);
    lg_add_edge(lg_bfs, numbers[4], numbers[7]);
    lg_add_edge(lg_bfs, numbers[5], numbers[2]);
    lg_add_edge(lg_bfs, numbers[6], numbers[3]);
    lg_add_edge(lg_bfs, numbers[7], numbers[3]);
    lg_add_edge(lg_bfs, numbers[7], numbers[4]);
   	bfs_list_graph(lg_bfs, 1, x, y);

   	printf("\n---TEST FLOYD WARSHALL---\n");
	floyd_warshall(mg);

	lg_free(lg);
	lg_free(lg_bfs);
	mg_free(mg);
	return 0;
}
