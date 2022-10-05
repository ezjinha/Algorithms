#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int W, H;
int wafer[10][25];
int selected[10][25];
int memo[1 << 10][25];
int max_chip;

void select(int y, int x)
{
	selected[y][x] = selected[y + 1][x] = selected[y][x + 1] = selected[y + 1][x + 1] = 1;
}

void clear(int y, int x)
{
	selected[y][x] = selected[y + 1][x] = selected[y][x + 1] = selected[y + 1][x + 1] = 0;
}

int selectable(int y, int x)
{
	if (wafer[y][x] || wafer[y + 1][x] || wafer[y][x + 1] || wafer[y + 1][x + 1]) return 0;
	if (selected[y][x] || selected[y + 1][x] || selected[y][x + 1] || selected[y + 1][x + 1]) return 0;
	return 1;
}

void dfs(int y, int x, int cnt, int selected)
{
	if (x >= W - 1)
	{
		max_chip = cnt > max_chip ? cnt : max_chip;
		return;
	}

	if (y >= H - 1) {
		if (memo[selected][x] >= cnt)
			return;

		memo[selected][x] = cnt;
		dfs(0, x + 1, cnt, 0);
		return;
	}
	
	if (selectable(y, x)) {
		select(y, x);
		dfs(y + 2, x, cnt + 1, selected | (1 << y));
		clear(y, x);
	}

	dfs(y + 1, x, cnt, selected);
}

void input()
{
	scanf("%d %d", &H, &W);

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			scanf("%d", &wafer[i][j]);
			selected[i][j] = 0;
		}
	}

	for (int i = 0; i < (1 << H); i++)
	{
		for (int j = 0; j < W; j++)
		{
			memo[i][j] = -1;
		}
	}

	max_chip = 0;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		input();
		dfs(0, 0, 0, 0);
		printf("%d\n", max_chip);
	}

	return 0;
}