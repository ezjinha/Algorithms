#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct _Node {
	int y;
	int x;
} Node;

const int dy[] = { 0, 1, -1, 0 };
const int dx[] = { 1, 0, 0, -1 };

int maze[16][16];
int visited[16][16];
int finished;

void move(int y, int x)
{
	if (maze[y][x] == 3)
	{
		finished = 1;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (nx < 0 || nx > 15 || ny < 0 || ny > 15) continue;
		if (maze[ny][nx] == 1) continue;
		if (visited[ny][nx] != 0) continue;

		visited[ny][nx] = 1;
		move(ny, nx);
		visited[ny][nx] = 0;
	}
}

void input()
{
	finished = 0;
	memset(visited, 0, sizeof(int) * 16 * 16);
	visited[1][1] = 1;

	char line[100];
	for (int y = 0; y < 16; y++)
	{
		scanf("%s", line);
		for (int x = 0; x < 16; x++)
		{
			maze[y][x] = (int)(line[x] - '0');
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	for (int test_case = 1; test_case <= 10; test_case++)
	{
		int T;
		scanf("%d", &T);
		input();
		move(1, 1);
		printf("#%d %d\n", test_case, finished);
	}

	return 0;
}