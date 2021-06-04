#include <stdio.h>
#include "utils.h"
#define NMAX 1000

int main()
{
	int N, xc[NMAX], yc[NMAX], raza[NMAX];
	int aux, aux2;
	int nr = 0;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d %d", &xc[i], &yc[i], &raza[i]);

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			aux = (xc[i] - xc[j]) * (xc[i] - xc[j]) + (yc[i] - yc[j]) * (yc[i] - yc[j]);
			aux2 = (raza[i] + raza[j]) * (raza[i] + raza[j]);
			if (aux <= aux2)
				nr++;
		}
	}

	printf("%d\n", nr);
	
    return 0;
}
