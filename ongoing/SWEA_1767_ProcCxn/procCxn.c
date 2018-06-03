#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef enum { false, true } bool;

typedef struct
{
	int y;
	int x;
} Coord;

Coord core[12];		// array of core coordination
int** cell;			// array of cell
int N;				// size of cell	
int K;				// size of core

void input()
{
	memset(core, -1, 12);
	K = -1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &cell[i][j]);

			if (cell[i][j] == 1)
			{
				K++;
				core[K].y = i;
				core[K].x = j;
			}
		}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;			// count of testcase
	scanf("%d", &T);

	//for (int test_case = 1; test_case <= T; test_case++)
	for (int test_case = 1; test_case <= 1; test_case++)
	{
		scanf("%d", &N);

		cell = (int**)malloc(sizeof(int*) * N);

		// malloc
		for (int i = 0; i < N; i++)
			cell[i] = (int*)malloc(sizeof(int) * N);

		input();

		printf("%d", K);
		for (int i = 0; i <= K; i++)
			printf("%d, %d\n", core[i].y, core[i].x);

		// delete
		for (int i = 0; i < N; i++)
			free(cell[i]);
		free(cell);
	}
	return 0;
}