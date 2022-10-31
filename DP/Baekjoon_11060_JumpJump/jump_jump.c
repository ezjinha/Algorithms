#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const int INF = (1<<30);
int n;	// 1 <= n <= 1000
int maze[1001];
int dp[1001];

int min(int a, int b)
{
	return b > a ? a : b;
}

void jump()
{
	dp[1] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= maze[i] + i; j++)
		{
			if (j > n) continue;
			dp[j] = min(dp[i] + 1, dp[j]);
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &maze[i]);
		dp[i] = INF;
	}

	jump();
	printf("%d\n", dp[n] == INF ? -1 : dp[n]);

	return 0;
}