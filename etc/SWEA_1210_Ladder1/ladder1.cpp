#include <fstream>
#include <iostream>

using namespace std;

const int LEFT = -1;
const int DOWN = 0;
const int RIGHT = 1;

int ladder[100][100];		// array for ladder
int dirDown;			// flag for check direction of move
bool isFound;			// flag for checking if X is found
int ans;			// answer

bool rightMovable(int y, int x)
{
	int nx = x + 1;
	if (nx < 100 && ladder[y][nx] == 1)
		return true;
	return false;
}

bool leftMovable(int y, int x)
{
	int nx = x - 1;
	if (nx >= 0 && ladder[y][nx] == 1)
		return true;
	return false;
}

void move(int y, int x, int dir)
{
	if (y == 99)
	{
		if (ladder[y][x] == 2)
			isFound = true;
		return;
	}

	if (dir == LEFT)
	{
		if (leftMovable(y, x))
			move(y, x - 1, LEFT);
		else
			move(y + 1, x, DOWN);
	}
	else if (dir == RIGHT)
	{
		if (rightMovable(y, x))
			move(y, x + 1, RIGHT);
		else
			move(y + 1, x, DOWN);
	}
	else	// dir == DOWN
	{
		if (leftMovable(y, x))
			move(y, x - 1, LEFT);
		else if (rightMovable(y, x))
			move(y, x + 1, RIGHT);
		else
			move(y + 1, x, DOWN);
	}
}

int main()
{
	ifstream cin("input.txt");

	int T;			// count of testcase
	
	for (int test_case = 1; test_case <= 10; test_case++)
	{
		isFound = false;
		cin >> T;

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				cin >> ladder[i][j];

		for (int i = 0; i < 100; i++)
		{
			if (ladder[0][i] == 1)
			{
				move(0, i, DOWN);

				if (isFound)
				{
					ans = i;
					break;
				}
			}
		}
		cout << '#' << test_case << ' ' << ans << endl;
	}

	return 0;
}
