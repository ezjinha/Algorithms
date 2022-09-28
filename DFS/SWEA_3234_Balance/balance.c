#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#include <time.h>

int N;
int weight[10];
int used[10];
int memo[10][1300][1300];

void setState(int* state, int i)
{
	*state |= (0x1 << i);
}

void clearState(int* state, int i)
{
	*state &= ~(0x1 << i);
}

int getCount(int lev, int left_state, int right_state, int left_weight, int right_weight)
{
	if (left_weight < right_weight) return 0;
	if (lev == N) return 1;
	if (memo[lev][left_state][right_state] != -1) return memo[lev][left_state][right_state];

	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (used[i] == 0)
		{
			used[i] = 1;

			setState(&left_state, i);
			cnt += getCount(lev + 1, left_state, right_state, left_weight + weight[i], right_weight);
			clearState(&left_state, i);

			setState(&right_state, i);
			cnt += getCount(lev + 1, left_state, right_state, left_weight, right_weight + weight[i]);
			clearState(&right_state, i);

			used[i] = 0;
		}
	}
	memo[lev][left_state][right_state] = cnt;
	return cnt;
}

void init()
{
	int limit = (1 << N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < limit; j++)
		{
			for (int k = 0; k < limit; k++)
			{
				memo[i][j][k] = -1;
			}
		}
	}
}

void input()
{
	scanf("%d", &N);
	memset(used, 0, sizeof(int) * 10);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &weight[i]);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	//for (int test_case = 1; test_case <= 1; test_case++)
	{
		time_t start = clock();
		input();
		init();
		
		printf("#%d %d %d ms\n", test_case, getCount(0, 0, 0, 0, 0), clock() - start);
	}
}