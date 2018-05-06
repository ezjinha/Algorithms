#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int map[101][101];						// map
int N;									// number of dragon curve
int X, Y;								// coordinate
int D;									// start direction
int G;									// generation

// right, up, left, down (0, 1, 2, 3)

int countSquare()
{
	int cnt = 0;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (map[i][j] == 1 &&
				map[i + 1][j] == 1 &&
				map[i][j + 1] == 1 &&
				map[i + 1][j + 1] == 1)
				cnt++;
		}
	}

	return cnt;
}

void move(int y, int x, vector<int>& dir)
{
	if (dir.empty())
		return;

	int ny, nx;

	switch (*dir.begin())
	{
	case 0:
		ny = y;
		nx = x + 1;
		break;
	case 1:
		ny = y - 1;
		nx = x;
		break;
	case 2:
		ny = y;
		nx = x - 1;
		break;
	case 3:
		ny = y + 1;
		nx = x;
		break;
	}
	map[ny][nx] = 1;
	dir.erase(dir.begin());
	move(ny, nx, dir);
}

void makeDir(vector<int>& dir, int n)
{
	if (n == G)
		return;
	
	vector<int> temp;
	for (auto iter = dir.rbegin(); iter != dir.rend(); iter++)
	{
		if (*iter == 3)
			temp.push_back(0);
		else
			temp.push_back(*iter + 1);
	}

	for (int i = 0; i < (int)temp.size(); i++)
		dir.push_back(temp.at(i));

	makeDir(dir, n + 1);
}

void reproduce()
{
	vector<int> dir;		// save direction
	dir.push_back(D);
	makeDir(dir, 0);
	move(Y, X, dir);
}

void initialize()
{
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			map[i][j] = 0;
}

int main()
{
	fstream cin("input.txt");

	//for (int test_case = 1; test_case <= 1; test_case++)
	for (int test_case = 1; test_case <= 4; test_case++)
	{
		initialize();
		
		// input
		cin >> N;

		for (int i = 0; i < N; i++)
		{
			cin >> X >> Y >> D >> G;
			map[Y][X] = 1;
			reproduce();
		}

		cout << countSquare() << endl;
	}

	return 0;
}