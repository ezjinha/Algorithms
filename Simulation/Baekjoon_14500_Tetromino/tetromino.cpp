#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int N;						// height
int M;						// width
int paper[500][500];		// array of paper

const int LUDIAG = 0;
const int UP     = 1;
const int LEFT   = 2;
const int DOWN   = 3;
const int RIGHT  = 4;
const int RDDIAG = 5;
const int dy[] = {-1, -1, 0, 1, 0, 1};
const int dx[] = {-1, 0, -1, 0, 1, 1};

// shape of tetromino
// array<array<int, COL>, ROW>
const vector<vector<int>> I = {{DOWN, DOWN, DOWN}, {RIGHT, RIGHT, RIGHT}};
const vector<vector<int>> L = {{DOWN, DOWN, RIGHT}, {RIGHT, RIGHT, UP}, {UP, UP, LEFT}, {LEFT, LEFT, DOWN},
							   {DOWN, DOWN, LEFT}, {RIGHT, RIGHT, DOWN}, {UP, UP, RIGHT}, {LEFT, LEFT, UP}};
const vector<vector<int>> O = {{DOWN, RIGHT, UP}};
const vector<vector<int>> T = {{RDDIAG, LEFT, DOWN}, {RIGHT, UP, RDDIAG}, {LUDIAG, RIGHT, UP}, {LEFT, LEFT, RDDIAG}};
const vector<vector<int>> Z = {{DOWN, RIGHT, DOWN}, {RIGHT, UP, RIGHT}, {DOWN, LEFT, DOWN}, {RIGHT, DOWN, RIGHT}};
const vector<vector<vector<int>>> TETRO = {I, L, O, T, Z};
int max_sum;

bool isInPaper(int y, int x)
{
	if ((y >= 0 && y < N) && (x >= 0 && x < M))
		return true;
	return false;
}

void putTetro(int y, int x)
{
	for (auto tetro : TETRO)
	{
		for (auto dir_list : tetro)
		{
			int sum = paper[y][x];
			int ny = y;
			int nx = x;
			for (size_t i = 0; i < 3; i++)
			{
				int dir = dir_list[i];
				ny = ny + dy[dir];
				nx = nx + dx[dir];

				if (!isInPaper(ny, nx))
					break;
				else
				{
					sum += paper[ny][nx];
					if (i == 2)
					{
						// compare with max_sum
						max_sum = max_sum < sum ? sum : max_sum;
					}
				}
			}
		}
	}
}

void findMaxValue()
{
	max_sum = 0;
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			putTetro(i, j);
		}
	}
}

int main()
{
	ifstream cin("input.txt");

	for (int test_case = 1; test_case <= 3; test_case++)
	{
		// input
		cin >> N >> M;
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < M; j++)
			{
				cin >> paper[i][j];
			}
		}

		findMaxValue();
		cout << max_sum << endl;
	}

	return 0;
}
