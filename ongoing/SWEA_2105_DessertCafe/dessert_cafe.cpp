#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int N;			// square side
int** area;		// dessert cafe area
int type_max;	// maximum value of count of dessert type

// check direction
int cdy[] = { -1, 1, 0, 0 };
int cdx[] = { 0, 0, 1, -1 };

// move direction
int mdy[] = { -1, -1, 1, 1 };
int mdx[] = { -1, 1, 1, -1 };

void extendRoute(vector<int>& v, int y, int x, int dir)
{
	int cy = y + cdy[dir];
	int cx = x + cdx[dir];

	vector<int>::iterator iter;
	iter = find(v.begin(), v.end(), area[cy][cx]);
	if (iter != v.end())
		return;


	for (int i = 0; i < 4; i++)
	{
		int my = y + mdy[i];
		int mx = x + mdx[i];

		if (my > 0 && my < N - 1 && mx > 0 && mx < N - 1)
			extendRoute(v, my, mx);
	}
}

void move()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			vector<int> v;
			if (i != 0 && i != N - 1 && j != 0 && j != N - 1)
			{
				for (int k = 0; k < 4; k++)
				{
					extendRoute(v, i, j, k);
				}
			}
		}
	}
}

int main()
{
	ifstream cin("input.txt");
	int T;		// count of testcase
	cin >> T;

	//for (int test_case = 1; test_case <= T; test_case++)
	for (int test_case = 1; test_case <= 1; test_case++)
	{
		type_max = 0;
		cin >> N;

		// new
		area = new int*[N];
		for (int i = 0; i < N; i++)
			area[i] = new int[N];

		// input
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> area[i][j];

		// print
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << area[i][j];
		//	cout << endl;
		//}

		// delete
		for (int i = 0; i < N; i++)
			delete[] area[i];
		delete[] area;
	}

	return 0;
}