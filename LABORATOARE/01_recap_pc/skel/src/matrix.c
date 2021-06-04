#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, m;
	int **mat = NULL;

	scanf("%d %d", &n, &m);
	mat = (int **)malloc(n * sizeof(int *));
	if (!mat) {
		free(mat);
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		mat[i] = (int *)malloc(m * sizeof(int));
		if (!mat[i]) {
			free(mat[i]);
			exit(1);
		}

		for (int j = 0; j < m; j++)
			scanf("%d", &mat[i][j]);
	}

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n; i++)
		free(mat[i]);
	free(mat);

	return 0;
}
