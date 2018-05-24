#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

class Coord
{
public:
	int y;
	int x;

	Coord() {}
	Coord(int _y, int _x) : y(_y), x(_x) {}
};

int W;		// width
int H;		// height
int N;		// count of intersection
int** map;	// array of map
Coord* cd;	// array of given coordination

int dy[] = { -1, 1, 0, 0, -1, 1 };
int dx[] = { 0, 0, -1, 1, -1, 1 };

const int UNVISITED = 0;

void initializeMap()
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			map[i][j] = 0;
}

void move()
{
	queue<Coord> q;
	int cnt = 0;
	
	for (int i = 0; i < N; i++)
	{
		q.push(cd[i]);

		while (!q.empty())
		{
			int y = cd[i].y;
			int x = cd[i].x;

			for (int j = 0; j < 6; j++)
			{
				int ny = y + dy[j];
				int nx = x + dx[j];

				if ((ny >= 0 && ny < H) &&
					(nx >= 0 && nx < W) &&
					(map[ny][nx] == 0))
				{

				}
			}
		}
	}
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
		map = new int*[H];
		for (int i = 0; i < H; i++)
			map[i] = new int[W]();

		for (int i = 0; i < N; i++)
		{
			int x, y;
			cin >> y >> x;
			cd[i] = Coord(y - 1, x - 1);
		}

		// print
		//for (int i = 0; i < H; i++)
		//{
		//	for (int j = 0; j < W; j++)
		//	{
		//		cout << map[i][j] << ' ';
		//	}
		//	cout << endl;
		//}

		delete[] cd;
		for (int i = 0; i < H; i++)
			delete[] map[i];
		delete[] map;
	}

	return 0;
}