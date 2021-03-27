#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
* Functia primeste o matrice si numarul sau de linii si de coloane si afiseaza
* suma elementelor de pe diagonala matricei.
*
* @param m      pointer catre matrice
* @param rows   numarul de linii ale matricei
* @param cols   numarul de coloane ale matricei
*/
void printDiagonalSum(int** m, int rows, int cols)
{
   int min = rows;
   if (cols < rows)
   	min = cols;

   int sum = 0;
   for (int i = 0; i < min; i++)
   	sum += m[i][i];

   printf("%d\n", sum);
}

/* NU MODIFICATI MAINUL! */
int main(void)
{
    int r, c, rows, cols;
    int** m;

    scanf("%d %d", &rows, &cols);

    m = malloc(rows * sizeof(*m));

    for (r = 0; r != rows; ++r)
    {
        m[r] = malloc(cols * sizeof(**m));

        for (c = 0; c != cols; ++c)
        {
            scanf("%d", &m[r][c]);
        }
    }

    printDiagonalSum(m, rows, cols);

    for (r = 0; r != rows; ++r)
    {
        free(m[r]);
    }
    free(m);

    return 0;
}
