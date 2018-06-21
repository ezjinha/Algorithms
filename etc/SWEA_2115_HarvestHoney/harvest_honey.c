#define _CRT_SECURE_NO_WARNINGS
typedef enum {false, true} bool;
#include <stdio.h>
#include <stdlib.h>

int** hive;		// map of hive
bool** empty;	// check if empty
int N;			// size of hive
int M;			// selective hive
int C;			// maximum honey amount
int hy, hx;		// harvested coordination
int hcnt;		// harvested count
int max_profit;	// maximum profit

void harvest(int y, int x, int cnt, int total, int profit)
{
	if (y == N - 1 && x == N - 1)
		return;
	else if (x == N - 1)
	{
		if (max_profit < profit)
		{
			hy = y;
			hx = x;
			hcnt = cnt;
			max_profit = profit;
		}

	}
	else
	{
		// normal case
		int nx = x + 1;
		int nTotal = total + hive[y][nx];
		int nProfit = profit + hive[y][nx] * hive[y][nx];

		if (nTotal > C)
		{

		}
		harvest(y, nx, cnt + 1, nTotal, nProfit);
	}

}

void input()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &hive[i][j]);
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;		// count of testcase
	scanf("%d", &T);

	//for (int test_case = 1; test_case <= T; test_case++)
	for (int test_case = 1; test_case <= 1; test_case++)
	{
		max_profit = 0;
		scanf("%d %d %d", &N, &M, &C);

		// malloc
		hive = (int**)malloc(sizeof(int*) * N);
		empty = (bool**)malloc(sizeof(bool*) * N);
		for (int i = 0; i < N; i++)
		{
			hive[i] = (int*)malloc(sizeof(int) * N);
			empty[i] = (bool*)calloc(N, sizeof(bool) * N);
		}

		input();


		// free
		for (int i = 0; i < N; i++)
		{
			free(hive[i]);
			free(empty[i]);
		}
		free(hive);
		free(empty);
	}
	
	return 0;
}