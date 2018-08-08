#include <fstream>
#include <iostream>
using namespace std;

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

Microbe gp[1000];		// array of microbe
int N;					// number of cell
int M;					// isolation time
int K;					// number of group

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