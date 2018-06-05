#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Coord
{
public:
	int y;
	int x;
};

int W;			// width
int H;			// height
int N;			// count of intersection
Coord* cd;		// array of given coordination

int moveCnt()
{
	int cnt = 0;

	for (int i = 0; i < N - 1; i++)
	{
		Coord start = cd[i];
		Coord finish = cd[i + 1];

		if ((start.y > finish.y) && (start.x < finish.x))			// Quadrant 1
			cnt += (start.y - finish.y) + (finish.x - start.x);
		else if ((start.y > finish.y) && (start.x > finish.x))		// Quadrant 2
			cnt += max((start.y - finish.y), (start.x - finish.x));
		else if ((start.y < finish.y) && (start.x > finish.x))		// Quadrant 3
			cnt += (finish.y - start.y) + (start.x - finish.x);
		else if ((start.y < finish.y) && (start.x < finish.x))		// Quadrant 4
			cnt += max((finish.y - start.y), (finish.x - start.x));
		else if (start.y == finish.y)								// X-axis
			cnt += abs(start.x - finish.x);
		else if (start.x == finish.x)								// Y-axis
			cnt += abs(start.y - finish.y);
	}

	return cnt;
}

int main()
{
	ifstream cin("input.txt");
	int T;		// count of test case
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		// input
		cin >> W >> H >> N;

		cd = new Coord[N];

		for (int i = 0; i < N; i++)
		{
			int x, y;
			cin >> x >> y;
			cd[i].y = y - 1;
			cd[i].x = x - 1;
		}

		cout << '#' << test_case << ' ' << moveCnt() << endl;

		delete[] cd;
	}

	return 0;
}
