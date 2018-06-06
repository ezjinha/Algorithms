#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef enum { false, true } bool;

typedef struct
{
	int y;
	int x;
	int len[4];				// valid length by direction (If not, value is -1)
	int len_cnt;			// count of valid line
} Coord;

Coord core[12];				// array of core coordination
int** cell;					// array of cell
int N;						// size of cell	
int K;						// size of core
int core_cnt;				// count of core
int len_sum;				// length sum
int max_cnt;				// maximum count of core
int min_len;				// minimum length of line

#define DOWN  0
#define RIGHT 1
#define UP    2
#define LEFT  3

int dy[] = { 1, 0, -1, 0 };
int dx[] = { 0, 1, 0, -1 };

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

//void calculateLength()
//{
//	for (int i = 0; i < K; i++)
//	{
//		if (core[i].dir != -1)
//		{
//			core_cnt++;
//			len_sum += core[i].len;
//		}
//	}
//
//	if (max_cnt < core_cnt)
//	{
//		max_cnt = core_cnt;
//		min_len = len_sum;
//	}
//	else if (max_cnt == core_cnt)
//		min_len = min_len > len_sum ? len_sum : min_len;
//}

void connectLine()
{
	for (int i = 0; i < K; i++)
	{
		int min_len = N;
		int min_dir = 0;

		for (int j = 0; j < 4; j++)
			if (min_len > core[i].len[j])
			{
				min_len = core[i].len[j];
				min_dir = j;
			}

		int y = core[i].y;
		int x = core[i].x;

		for (int j = 0; j < min_len; j++)
		{
			y += dy[min_dir];
			x += dx[min_dir];
			cell[y][x] = 2;
		}
	}
}

//void findShortestLine(Coord* cod)
//{
//	int y = cod->y;
//	int x = cod->x;
//	int min_dir = -1;
//	int min_line = 1 << 30;
//
//	for (int i = 0; i < 4; i++)
//	{
//		int cnt = 0;
//		int ny = y + dy[i];
//		int nx = x + dx[i];
//
//		while (true)
//		{
//			if (ny == -1 || ny == N || nx == -1 || nx == N)
//			{
//				if (min_line > cnt)
//				{
//					min_dir = i;
//					min_line = cnt;
//				}
//				break;
//			}
//			else if (cell[ny][nx] == 1 || cell[ny][nx] == 2)
//				break;
//			else
//			{
//				cnt += 1;
//				ny += dy[i];
//				nx += dx[i];
//			}
//		}
//	}
//
//	cod->dir = min_dir;
//	cod->len = min_line;
//
//	connectLine(*cod);
//}

//void makeSequences(int start, int n)
//{
//	if (n == K)
//	{
//		for (int i = 0; i < K; i++)
//			findShortestLine(&core[i]);
//
//		calculateLength();
//
//		if (max_cnt < core_cnt)
//		{
//			max_cnt = core_cnt;
//			min_len = len_sum;
//		}
//		else if (max_cnt == core_cnt)
//			min_len = min_len > len_sum ? len_sum : min_len;
//
//		removeLine();
//		core_cnt = 0;
//		len_sum = 0;
//
//		for (int i = 0; i < K; i++)
//			printf("(%d, %d)  ", core[i].x, core[i].y);
//		printf("\n");
//
//		return;
//	}
//
//	for (int i = start; i < K; i++)
//	{
//		swap(&core[start], &core[i]);
//		findShortestLine(&core[start]);
//		makeSequences(start + 1, n + 1);
//		swap(&core[start], &core[i]);
//	}
//}

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

void changeOrderByLine()
{
	for (int i = 0; i < K - 1; i++)
	{
		for (int j = i + 1; j < K; j++)
		{
			if (core[i].len_cnt > core[j].len_cnt)
				swap(&core[i], &core[j]);
		}
	}
}

void decideConnection()
{
	for (int i = 0; i < K; i++)
	{
		int y = core[i].y;
		int x = core[i].x;
		for (int j = 0; j < 4; j++)
		{
			int l = 0;
			int ny = y + dy[j];
			int nx = x + dx[j];

			while (true)
			{
				if (ny == -1 || ny == N || nx == -1 || nx == N)
				{
					core[i].len[j] = l;
					core[i].len_cnt += 1;
					break;
				}
				else if (cell[ny][nx] == 1)
				{
					core[i].len[j] = -1;
					break;
				}
				else
				{
					l += 1;
					ny += dy[j];
					nx += dx[j];
				}
			}
		}
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

		decideConnection();
		changeOrderByLine();




		//for (int i = 0; i < K; i++)
		//	printf("%d\n", core[i].len_cnt);

		//print
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		printf("%d ", cell[i][j]);
		//	printf("\n");
		//}

		//makeSequences(0, 0);
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

		//printf("#%d %d\n", test_case, min_len);

		// delete
		for (int i = 0; i < N; i++)
			free(cell[i]);
		free(cell);
	}
	return 0;
}
