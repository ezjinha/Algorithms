#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

// DOWN, UP, LEFT, RIGHT
const int dy[] = { 1, -1, 0, 0 };
const int dx[] = { 0, 0, -1, 1 };

const int MAX_SIZE = 500;
const int DEAD = 1;
const int INACTIVE = 2;
const int ACTIVE = 3;

int grid[MAX_SIZE][MAX_SIZE];			// cell array
int state[MAX_SIZE][MAX_SIZE];			// array for check state

struct Cell
{
	int y;
	int x;
	int t;					// elapsed time
	int st;					// state time

	bool operator<(const Cell& cell) const
	{
		if (t == cell.t)
			return grid[y][x] < grid[cell.y][cell.x];
		return t > cell.t;
	}
};

int N;						// vertical size
int M;						// horizontal size
int K;						// iucubation time
priority_queue<Cell> q;				// queue for cell
int cell_num;					// number of cell

void incubate()
{
	while (!q.empty())
	{
		int y = q.top().y;
		int x = q.top().x;
		int t = q.top().t;
		int st = q.top().st;

		if (t == K)
		{
			cell_num = q.size();
			break;
		}

		if (state[y][x] == INACTIVE)
		{
			int n_st = st + 1;
			if (n_st == grid[y][x])
			{
				state[y][x] = ACTIVE;
				n_st = 0;
			}
			q.push({ y, x, t + 1, n_st });
		}
		else if (state[y][x] == ACTIVE)
		{
			int n_st = st + 1;

			for (int i = 0; i < 4; i++)
			{
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (grid[ny][nx] == 0)
				{
					grid[ny][nx] = grid[y][x];
					state[ny][nx] = INACTIVE;
					q.push({ ny, nx, t + 1, 0 });
				}
			}

			if (n_st == grid[y][x])
			{
				state[y][x] = DEAD;
			}
			else
			{
				q.push({ y, x, t + 1, n_st });
			}
		}
		
		q.pop();
	}
}

void init()
{
	while (!q.empty())
		q.pop();

	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
		{
			grid[i][j] = 0;
			state[i][j] = 0;
		}
}

int main()
{
	ifstream cin("input.txt");
	int T;						// number of testcase
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		init();
		// input
		cin >> N >> M >> K;
		int st_y = (MAX_SIZE - N) / 2;
		int st_x = (MAX_SIZE - M) / 2;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> grid[st_y + i][st_x + j];
				if (grid[st_y + i][st_x + j] != 0)
				{
					q.push({ st_y + i, st_x + j, 0, 0 });
					state[st_y + i][st_x + j] = INACTIVE;
				}
			}
		}
		incubate();

		cout << '#' << test_case << ' ' << cell_num << endl;
	}

	return 0;
}
