#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef enum { false, true } bool;

#define LEFT -1
#define DOWN  0
#define RIGHT  1

int ladder[100][100];		// array for ladder
bool isMin;					// check if minimum value
int minV;					// minimum value
int ans;					// answer

bool rightMovable(int y, int x)
{
	int nx = x + 1;
	if ((nx < 100) && (ladder[y][nx] == 1))
		return true;
	return false;
}

bool leftMovable(int y, int x)
{
	int nx = x - 1;
	if ((nx >= 0) && (ladder[y][nx] == 1))
		return true;
	return false;
}

void move(int y, int x, int dir, int cnt)
{
	if (y == 99)
	{
		if (minV > cnt)
		{
			minV = (minV > cnt) ? cnt : minV;
			isMin = true;
		}
		return;
	}

	if (dir == LEFT)
	{
		if (leftMovable(y, x))
			move(y, x - 1, LEFT, cnt + 1);
		else
			move(y + 1, x, DOWN, cnt + 1);
	}
	else if (dir == RIGHT)
	{
		if (rightMovable(y, x))
			move(y, x + 1, RIGHT, cnt + 1);
		else
			move(y + 1, x, DOWN, cnt + 1);
	}
	else	// dir == DOWN
	{
		if (leftMovable(y, x))
			move(y, x - 1, LEFT, cnt + 1);
		else if (rightMovable(y, x))
			move(y, x + 1, RIGHT, cnt + 1);
		else
			move(y + 1, x, DOWN, cnt + 1);
	}
}

void findStart()
{
	for (int i = 0; i < 100; i++)
	{
		if (ladder[0][i] == 1)
		{
			isMin = false;
			move(0, i, DOWN, 0);
			if (isMin)
				ans = i;
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	
	for (int test_case = 1; test_case <= 10; test_case++)
	{
		scanf("%d", &T);
		minV = 1 << 30;

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				scanf("%d", &ladder[i][j]);

		findStart();

		printf("#%d %d\n", T, ans);
	}

	return 0;
}