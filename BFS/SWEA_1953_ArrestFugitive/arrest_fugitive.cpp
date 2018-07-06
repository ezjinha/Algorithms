#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
	int y;
	int x;
	int l;
	Coord(int _y, int _x, int _l) : y(_y), x(_x), l(_l) {}
};

// UP, DOWN, LEFT, RIGHT
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int map[50][50];		// underground tunnel map
bool visited[50][50];	// underground tunnel map
int N;					// vertical line
int M;					// horizontal line
int R, C;				// location (y, x)
int L;					// run time
int ans;				// answer

bool isMovable(int tunnel, int dir)
{
	switch (tunnel)
	{
	case 0:
		return false;
	case 1:
		break;
	case 2:
		if (dir == 2 || dir == 3)
			return false;
		break;
	case 3:
		if (dir == 0 || dir == 1)
			return false;
		break;
	case 4:
		if (dir == 1 || dir == 2)
			return false;
		break;
	case 5:
		if (dir == 0 || dir == 2)
			return false;
		break;
	case 6:
		if (dir == 0 || dir == 3)
			return false;
		break;
	case 7:
		if (dir == 1 || dir == 3)
			return false;
		break;
	}

	return true;
}

void findLocation()
{
	ans = 1;
	queue<Coord> q;
	q.push(Coord(R, C, 1));
	visited[R][C] = true;

	while (int l = q.front().l < L)
	{
		int y = q.front().y;
		int x = q.front().x;

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if ((ny >= 0 && ny < N) &&
				(nx >= 0 && nx < M) &&
				!visited[ny][nx] &&
				isMovable(map[y][x], i))
			{
				visited[ny][nx] = true;
				q.push(Coord(ny, nx, ++l));
				ans++;
			}
		}
		q.pop();
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
		// input
		cin >> N >> M >> R >> C >> L;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				cin >> map[i][j];
				visited[i][j] = false;
			}

		findLocation();

		cout << '#' << test_case << ' ' << ans << endl;
	}

	return 0;
}
