#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>

int t, n, cnt, res, sx, sy;
int check[101];
int visited[21][21];
int map[22][22];

//현재 상태를 나타내줌
//mode = {0, 1, 2, 3, 4}
void solve(int x, int y, int mode)
{
	cnt++;
	check[map[x][y]] += 1;
	visited[x][y] += 1;

	if (mode == 4 && visited[x][y] == 2)
	{
		if (res < cnt - 1)
		{
			res = cnt - 1;
		}
	}
	else
	{
		if (mode == 0)
		{
			if (!check[map[x + 1][y + 1]] && map[x][y] != 0)
			{
				solve(x + 1, y + 1, 1);
			}
		}
		else if (mode == 1)
		{
			if (!check[map[x + 1][y + 1]] && map[x + 1][y + 1] != 0)
			{
				solve(x + 1, y + 1, 1);
			}
			if (!check[map[x + 1][y - 1]] && map[x + 1][y - 1] != 0)
			{
				solve(x + 1, y - 1, 2);
			}
		}
		else if (mode == 2)
		{
			if (!check[map[x + 1][y - 1]] && map[x + 1][y - 1] != 0)
			{
				solve(x + 1, y - 1, 2);
			}
			if (!check[map[x - 1][y - 1]] && map[x - 1][y - 1] != 0)
			{
				solve(x - 1, y - 1, 3);
			}
		}
		else if (mode == 3)
		{
			if (!check[map[x - 1][y - 1]] && map[x - 1][y - 1] != 0)
			{
				solve(x - 1, y - 1, 3);
			}
			if (sx == x - 1 && sy == y + 1)
			{
				solve(x - 1, y + 1, 4);
			}
			else
			{
				if (!check[map[x - 1][y + 1]] && map[x - 1][y + 1] != 0)
				{
					solve(x - 1, y + 1, 4);
				}
			}
		}
		else
		{
			if (sx == x - 1 && sy == y + 1)
			{
				solve(x - 1, y + 1, 4);
			}
			else
			{
				if (!check[map[x - 1][y + 1]] && map[x - 1][y + 1] != 0)
				{
					solve(x - 1, y + 1, 4);
				}
			}
		}
	}

	cnt--;
	check[map[x][y]] -= 1;
	visited[x][y] -= 1;
}

void init()
{
	memset(map, 0, sizeof(map));
	res = -1;
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d", &n);
		init();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}

		for (int i = 1; i < n; i++) {
			for (int j = 2; j < n; j++) {
				sx = i;
				sy = j;
				solve(i, j, 0);
			}
		}

		printf("#%d %d\n", tc, res);
	}
}