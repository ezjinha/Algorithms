#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int** hive;		// map of hive
int N;			// size of hive
int M;			// selective hive
int C;			// maximum honey amount
int hy, hx;		// harvested coordination
int hcnt;		// harvested count
int max_profit;		// maximum profit

void harvest()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int cnt = 0;
			int total = 0;
			int profit = 0;
			int k = j;

			while (1)
			{
				if (hive[i][k] == -1 ||
					total + hive[i][k] > C ||
					cnt == M)
					break;
				else if (k == N - 1)
				{
					total += hive[i][k];
					profit += hive[i][k] * hive[i][k];
					cnt++;
					break;
				}
				else
				{
					total += hive[i][k];
					profit += hive[i][k] * hive[i][k];
				}

				cnt++;
				k++;
			}

			if (max_profit < profit)
			{
				hy = i;
				hx = k;
				hcnt = cnt;
				max_profit = profit;
			}
		}
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
	for (int test_case = 1; test_case <= 3; test_case++)
	{
		max_profit = 0;
		scanf("%d %d %d", &N, &M, &C);

		// malloc
		hive = (int**)malloc(sizeof(int*) * N);
		for (int i = 0; i < N; i++)
		{
			hive[i] = (int*)malloc(sizeof(int) * N);
		}

		input();

		harvest();
		int temp = max_profit;
		max_profit = 0;
		printf("%d %d %d\n", hy, hx, hcnt);
		for (int i = 0; i < hcnt; i++)
			hive[hy][hx - i] = -1;
		harvest();
		printf("%d %d %d\n", hy, hx, hcnt);

		printf("#%d %d\n", test_case, temp + max_profit);

		// free
		for (int i = 0; i < N; i++)
			free(hive[i]);
		free(hive);
	}
	
	return 0;
}
