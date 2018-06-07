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
bool visited[12];	// check if visited
int** cell;			// array of cell
int N;				// size of cell	
int K;				// size of core
int core_cnt;		// count of core
int len_sum;		// length sum
int max_cnt;		// maximum count of core
int min_len;		// minimum length of line

#define DOWN  0
#define RIGHT 1
#define UP    2
#define LEFT  3

int dy[] = { 1, 0, -1, 0 };
int dx[] = { 0, 1, 0, -1 };

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

	if (max_cnt < core_cnt)
	{
		max_cnt = core_cnt;
		min_len = len_sum;
	}
	else if (max_cnt == core_cnt)
		min_len = min_len > len_sum ? len_sum : min_len;
}

void connectLine(Coord cod)
{
	int y = cod.y;
	int x = cod.x;
	int dir = cod.dir;
	for (int i = 0; i < cod.len; i++)
	{
		y += dy[dir];
		x += dx[dir];
		cell[y][x] = 2;
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
		if (!visited[i])
		{
			visited[i] = true;
			findShortestLine(&core[start]);
			makeSequences(i + 1, n + 1);
		}
		visited[i] = false;
		//swap(&core[start], &core[i]);
		//makeSequences(start + 1, n + 1);
		//swap(&core[start], &core[i]);
	}
}

//void makeVortexSequence(int y, int x, int dir, int lev, int cnt)
//{
//	if (y == 0 || y == N - 1 || x == 0 || x == N - 1)
//		return;
//
//	for (int i = 0; i < lev; i++)
//	{
//		if (cell[y][x] == 1)
//		{
//			core[K].y = y;
//			core[K].x = x;
//			core[K].dir = -1;
//			core[K].len = 0;
//			K++;
//		}
//
//		y += dy[dir];
//		x += dx[dir];
//	}
//
//	if (cnt == 1)
//	{
//		lev += 1;
//		cnt = 0;
//	}
//	else
//		cnt += 1;
//
//	if (dir == LEFT)
//		dir = DOWN;
//	else
//		dir += 1;
//
//	makeVortexSequence(y, x, dir, lev, cnt);
//}

//void connectLine()
//{
//	for (int i = 0; i < K; i++)
//	{
//		int y = core[i].y;
//		int x = core[i].x;
//
//		for (int j = 0; j < 4; j++)
//		{
//			int ny = y + dy[j];
//			int nx = x + dx[j];
//
//			if (core[i].isValid[j])
//			{
//				while (nx != -1 && nx != N && ny != -1 && ny != N)
//				{
//					if (cell[ny][nx] == 2)
//						cell[ny][nx] = 3;
//					else
//						cell[ny][nx] = 2;
//					ny += dy[j];
//					nx += dx[j];
//				}
//			}
//		}
//	}
//}

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
				core[K].y = i;
				core[K].x = j;
				K++;
			}
		}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;			// count of testcase
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	//for (int test_case = 1; test_case <= 1; test_case++)
	{
		max_cnt = 0;
		min_len = 1 << 30;

		scanf("%d", &N);

		cell = (int**)malloc(sizeof(int*) * N);

		// malloc
		for (int i = 0; i < N; i++)
			cell[i] = (int*)malloc(sizeof(int) * N);

		input();

		//print
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		printf("%d ", cell[i][j]);
		//	printf("\n");
		//}

		makeSequences(0, 0);
		//int start = (N - 1) / 2;
		//makeVortexSequence(start, start, DOWN, 1, 0);

		//for (int i = 0; i < K; i++)
		//{
		//	findShortestLine(&core[i]);
		//	printf("(%d, %d)\n", core[i].dir, core[i].len);
		//}

		//removeLine();

		//for (int i = 0; i < K; i++)
		//{
		//	findShortestLine(&core[i]);
		//	printf("(%d, %d)\n", core[i].dir, core[i].len);
		//}


		//calculateLength();

		// print
		//printf("%d", K);
		//for (int i = 0; i < K; i++)
		//	printf("%d, %d\n", core[i].y, core[i].x);

		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		printf("%d ", cell[i][j]);
		//	printf("\n");
		//}

		printf("#%d %d\n", test_case, min_len);

		// delete
		for (int i = 0; i < N; i++)
			free(cell[i]);
		free(cell);
	}
	return 0;
}
