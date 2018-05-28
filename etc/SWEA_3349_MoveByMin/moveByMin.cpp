#include <fstream>
#include <iostream>
#include <queue>
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
int max_cnt;	// max count of map
int** map;		// array of map
Coord* cd;		// array of given coordination

int dy[] = { -1, 1, 0, 0, -1, 1 };
int dx[] = { 0, 0, -1, 1, -1, 1 };

const int UNVISITED = 0;

void initializeMap()
{
	max_cnt = W * H + 1;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			map[i][j] = max_cnt;
}

int moveCnt()
{
	int cnt = 0;
	//queue<Coord> q;
	//
	//for (int i = 0; i < N - 1; i++)
	//{
	//	initializeMap();

	//	q.push(cd[i]);
	//	map[cd[i].y][cd[i].x] = 0;

	//	while (!q.empty())
	//	{
	//		int y = q.front().y;
	//		int x = q.front().x;
	//		int n = map[y][x];

	//		for (int j = 0; j < 6; j++)
	//		{
	//			int ny = y + dy[j];
	//			int nx = x + dx[j];

	//			if ((ny >= 0 && ny < H) &&
	//				(nx >= 0 && nx < W) &&
	//				(map[ny][nx] == max_cnt))
	//			{
	//				map[ny][nx] = min(map[ny][nx], n + 1);
	//			}
	//		}
	//	}

	//	cnt += map[cd[i + 1].y][cd[i + 1].x];
	//}

	for (int i = 0; i < N - 1; i++)
	{
		Coord start = cd[i];
		Coord finish = cd[i + 1];

		if ((start.y < finish.y) && (start.x < finish.x))			// Quadrant 1
			cnt += (finish.y - start.y) + (finish.x - start.x);
		else if ((start.y < finish.y) && (start.x > finish.x))		// Quadrant 2
			cnt += max((finish.y - start.y), (start.x - finish.x));
		else if ((start.y > finish.y) && (start.x > finish.x))		// Quadrant 3
			cnt += (start.y - finish.y) + (start.x - finish.x);
		else if ((start.y > finish.y) && (start.x < finish.x))		// Quadrant 4
			cnt += max((start.y - finish.y), (finish.x - start.x));
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
		map = new int*[H];
		for (int i = 0; i < H; i++)
			map[i] = new int[W];

		for (int i = 0; i < N; i++)
		{
			int x, y;
			cin >> y >> x;
			cd[i].y = y - 1;
			cd[i].x = x - 1;
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

		cout << moveCnt() << endl;

		for (int i = 0; i < H; i++)
			delete[] map[i];
		delete[] map;
		delete[] cd;
	}

	return 0;
}