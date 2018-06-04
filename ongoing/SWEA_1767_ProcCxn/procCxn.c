#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef enum { false, true } bool;

typedef struct
{
	int y;
	int x;
	int dir;
	int len;
} Coord;

Coord core[12];		// array of core coordination
int** cell;			// array of cell
int N;				// size of cell	
int K;				// size of core
int core_cnt;		// count of core
int len_sum;		// length sum
int max_cnt;		// maximum count of core
int min_len;		// minimum length of line

// UP(0), DOWN(1), LEFT(2), RIGHT(3)
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void swap(Coord* cod1, Coord* cod2)
{
	Coord temp = *cod1;
	*cod1 = *cod2;
	*cod2 = temp;
}

void removeLine()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (cell[i][j] == 2)
				cell[i][j] = 0;
}

void calculateLength()
{
	for (int i = 0; i < K; i++)
	{
		if (core[i].dir != -1)
		{
			core_cnt++;
			len_sum += core[i].len;
		}
	}
}

void connectLine(Coord cod)
{
	int y = cod.y;
	int x = cod.x;
	int dir = cod.dir;
	for (int i = 0; i < cod.len; i++)
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		cell[ny][nx] = 2;
	}
}

void findShortestLine(Coord* cod)
{
	int y = cod->y;
	int x = cod->x;
	int min_dir = -1;
	int min_line = 1 << 30;

	for (int i = 0; i < 4; i++)
	{
		int cnt = 0;
		int ny = y + dy[i];
		int nx = x + dx[i];

		while (true)
		{
			if (ny == -1 || ny == N || nx == -1 || nx == N)
			{
				if (min_line > cnt)
				{
					min_dir = i;
					min_line = cnt;
				}
				break;
			}
			else if (cell[ny][nx] == 1 || cell[ny][nx] == 2)
				break;
			else
			{
				cnt += 1;
				ny += dy[i];
				nx += dx[i];
			}
		}
	}

	cod->dir = min_dir;
	cod->len = min_line;

	connectLine(*cod);
}

void makeSequences(int start, int n)
{
	if (n == K)
	{
		//for (int i = 0; i < K; i++)
		//	findShortestLine(&core[i]);

		calculateLength();

		if (max_cnt < core_cnt)
		{
			max_cnt = core_cnt;
			min_len = len_sum;
		}
		else if (max_cnt == core_cnt)
			min_len = min_len > len_sum ? len_sum : min_len;

		removeLine();
		core_cnt = 0;
		len_sum = 0;

		//for (int i = 0; i < K; i++)
		//	printf("(%d, %d)  ", core[i].x, core[i].y);
		//printf("\n");

		return;
	}

	for (int i = start; i < K; i++)
	{
		swap(&core[start], &core[i]);
		findShortestLine(&core[start]);
		makeSequences(start + 1, n + 1);
		swap(&core[start], &core[i]);
	}
}

void input()
{
	memset(core, 0, 12);
	K = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &cell[i][j]);

			if (i != 0 && i != N - 1 &&
				j != 0 && j != N - 1 &&
				cell[i][j] == 1)
			{
				core[K].y   = i;
				core[K].x   = j;
				core[K].dir = -1;
				core[K].len = 0;
				K++;
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
		max_cnt = 0;
		min_len = 1 << 30;

		scanf("%d", &N);

		cell = (int**)malloc(sizeof(int*) * N);

		// malloc
		for (int i = 0; i < N; i++)
			cell[i] = (int*)malloc(sizeof(int) * N);

		input();

		makeSequences(0, 0);


		//for (int i = 0; i < K; i++)
		//{
		//	findShortestLine(&core[i]);
		//	printf("(%d, %d)\n", core[i].dir, core[i].len);
		//}

		// print
		//printf("%d", K);
		//for (int i = 0; i < K; i++)
		//	printf("%d, %d\n", core[i].y, core[i].x);

		printf("#%d %d\n", test_case, min_len);

		// delete
		for (int i = 0; i < N; i++)
			free(cell[i]);
		free(cell);
	}
	return 0;
}