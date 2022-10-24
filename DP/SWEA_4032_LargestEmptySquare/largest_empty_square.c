#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n;
int img[1001][1001];
int dp[1001][1001];
int max_len;

int min(int n1, int n2)
{
	return n1 < n2 ? n1 : n2;
}

int max(int n1, int n2)
{
	return n1 > n2 ? n1 : n2;
}

void checkImage()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (img[i][j] == 1)
			{
				dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
				max_len = max(dp[i][j], max_len);
			}
		}
	}
}

void input()
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		char line[1000];
		scanf("%s", line);
		for (int j = 1; j <= n; j++)
		{
			int dot = line[j - 1] - '0';
			img[i][j] = dot == 1 ? 0 : 1;
		}
	}
	max_len = 0;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		input();
		checkImage();

		printf("#%d %d\n", test_case, max_len);
	}

	return 0;
}