#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 500

int m, n;	// 0 < m, n <= 500
int map[MAX][MAX];
int dp[MAX][MAX];

const int dy[] = { -1, 0, 0, 1 };
const int dx[] = { 0, 1, -1, 0 };

int getCount(int y, int x)
{
	if (y == m - 1 && x == n - 1) return 1;
	if (dp[y][x] != -1) return dp[y][x];

	dp[y][x] = 0;
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny == m || nx < 0 || nx == n) continue;
		if (map[ny][nx] >= map[y][x]) continue;

		dp[y][x] += getCount(ny, nx);
	}

	return dp[y][x];
}

void input()
{
	scanf("%d %d", &m, &n);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			dp[i][j] = -1;
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	input();

	int answer = getCount(0, 0);

	printf("%d\n", answer);

	return 0;
}