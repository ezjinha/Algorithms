#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef enum { false, true } bool;

#define EAST  1
#define WEST  2
#define NORTH 3
#define SOUTH 4

int dy[] = { 0, 0, 0, -1, 1 };
int dx[] = { 0, 1, -1, 0, 0 };

int	map[20][20];	// map array
int N;				// vertical size
int M;				// horizontal size
int x;				// initial x
int y;				// initial y
int K;				// command number
int cmd[1000];		// command array
int dice[6];		// dice number array


void rollDice(int cmd)
{
	int temp_dice[6];
	for (int i = 0; i < 6; i++)
		temp_dice[i] = dice[i];
	switch (cmd)
	{
	case EAST:
	{
		dice[0] = temp_dice[3];
		dice[2] = temp_dice[0];
		dice[3] = temp_dice[5];
		dice[5] = temp_dice[2];
		break;
	}
	case WEST:
	{
		dice[0] = temp_dice[2];
		dice[2] = temp_dice[5];
		dice[3] = temp_dice[0];
		dice[5] = temp_dice[3];
		break;
	}
	case NORTH:
	{
		dice[0] = temp_dice[4];
		dice[1] = temp_dice[0];
		dice[4] = temp_dice[5];
		dice[5] = temp_dice[1];
		break;
	}
	case SOUTH:
	{
		dice[0] = temp_dice[1];
		dice[1] = temp_dice[5];
		dice[4] = temp_dice[0];
		dice[5] = temp_dice[4];
		break;
	}
	}
}

bool movable(int y, int x, int cmd)
{
	int ny = y + dy[cmd];
	int nx = x + dx[cmd];

	if (ny >= 0 && ny < N && nx >= 0 && nx < M)
		return true;
	return false;
}

void move()
{
	for (int i = 0; i < K; i++)
	{
		if (!movable(y, x, cmd[i]))
			continue;
		// move dice
		y += dy[cmd[i]];
		x += dx[cmd[i]];

		rollDice(cmd[i]);

		if (map[y][x] == 0)
			map[y][x] = dice[5];
		else
		{
			dice[5] = map[y][x];
			map[y][x] = 0;
		}

		printf("%d\n", dice[0]);
	}
}

void input()
{
	for (int i = 0; i < 6; i++)
		dice[i] = 0;
	scanf("%d %d %d %d %d", &N, &M, &y, &x, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	for (int i = 0; i < K; i++)
		scanf("%d", &cmd[i]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	int T;			// number of testcase
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	//for (int test_case = 1; test_case <= 1; test_case++)
	{
		input();
		move();
		printf("\n");
	}

	return 0;
}