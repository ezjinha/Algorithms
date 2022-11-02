#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INF 1 << 30

int n;
char block[1001];
int dp[1001];

int min(int a, int b)
{
	return b > a ? a : b;
}

void moveToNextBlock(int idx, char next)
{
	for (int i = idx + 1; i < n; i++)
	{
		if (block[i] == next)
		{
			dp[i] = min(dp[i], dp[idx] + (i - idx) * (i - idx));
		}
	}
}

void move()
{
	dp[0] = 0;
	for (int i = 0; i < n; i++)
	{
		int cur = block[i];
		int next = cur == 'B' ? 'O' : cur == 'O' ? 'J' : 'B';
		moveToNextBlock(i, next);
	}
}

void input()
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf(" %c", &block[i]);
		dp[i] = INF;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		input();
		move();

		printf("%d\n", dp[n - 1] == INF ? -1 : dp[n - 1]);
	}

	return 0;
}