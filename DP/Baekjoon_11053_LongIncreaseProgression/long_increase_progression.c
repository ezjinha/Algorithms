#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n;
int a[1001];
int dp[1001];
int max_len;

int main()
{
	freopen("input.txt", "r", stdin);

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}

	for (int i = 0; i < n; i++)
	{
		dp[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (a[j] < a[i] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		max_len = dp[i] > max_len ? dp[i] : max_len;
	}

	printf("%d\n", max_len);

	return 0;
}