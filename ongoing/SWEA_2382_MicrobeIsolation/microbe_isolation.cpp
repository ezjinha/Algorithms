#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int UP    = 1;
const int DOWN  = 2;
const int LEFT  = 3;
const int RIGHT = 4;

class Microbe
{
public:
	int y;
	int x;
	int num;
	int dir;

	Microbe() {}
	Microbe(int _y, int _x, int _num, int _dir) : y(_y), x(_x), num(_num), dir(_dir) {}
};

vector<Microbe> gp;		// array of microbe
int N;					// number of cell
int M;					// isolation time
int K;					// number of group

bool isOnEdge(Microbe& m)
{
	if (m.y == 0 || m.y == N - 1 || m.x == 0 || m.x == N - 1)
	{
		m.num /= 2;
		return true;
	}
	return false;
}

void move(Microbe& m)
{
	if (isOnEdge(m))
	{
		switch (m.dir)
		{
		case UP:
			m.dir = DOWN;
			break;
		case DOWN:
			m.dir = UP;
			break;
		case LEFT:
			m.dir = RIGHT;
			break;
		case RIGHT:
			m.dir = LEFT;
			break;
		}
	}
	else
	{
		switch (m.dir)
		{
		case UP:
			m.y -= 1;
			break;
		case DOWN:
			m.y += 1;
			break;
		case LEFT:
			m.x -= 1;
			break;
		case RIGHT:
			m.x += 1;
			break;
		}
	}

}

int main()
{
	ifstream cin("input.txt");
	int T;				// count of testcase
	cin >> T;

	//for (int test_case = 1; test_case <= T; test_case++)
	for (int test_case = 1; test_case <= 1; test_case++)
	{
		int y, x, num, dir;
		cin >> N >> M >> K;

		// input
		for (int i = 0; i < K; i++)
		{
			cin >> y >> x >> num >> dir;
			gp[i] = Microbe(y, x, num, dir);
		}
	}

	return 0;
}
