#include <fstream>
#include <iostream>

using namespace std;

const int LEFT = -1;
const int DOWN = 0;
const int RIGHT = 1;

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
	ifstream cin("input.txt");
	int T;					// number of testcase

	for (int test_case = 1; test_case <= 10; test_case++)
	//for (int test_case = 1; test_case <= 1; test_case++)
	{
		cin >> T;
		minV = 1 << 30;

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				cin >> ladder[i][j];

		findStart();

		cout << '#' << T << ' ' << ans << endl;
	}

	return 0;
}