#include <fstream>
#include <iostream>
#include <list>
using namespace std;

const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
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

list<Microbe> gp;		// vector of microbe
int N;					// number of cell
int M;					// isolation time
int K;					// number of group
int ans;				// answer

void calculate()
{
	for (auto it = gp.begin(); it != gp.end(); it++)
		ans += (*it).num;
}

void merge()
{
	for (auto it1 = gp.begin(); it1 != gp.end(); it1++)
	{
		Microbe& m1 = *it1;
		int max_num = m1.num;
		int num = m1.num;
		int dir = m1.dir;

		for (auto it2 = gp.begin(); it2 != gp.end(); it2++)
		{
			Microbe& m2 = *it2;
			if (m2.num != -1 && m1.y == m2.y && m1.x == m1.x)
			{
				num += m2.num;
				m2.num = -1;
				if (max_num < m2.num)
				{
					max_num = m2.num;
					dir = m2.num;
				}
			}
		}
		m1.num = num;
		m1.dir = dir;
		
		auto it = gp.begin();
		while (it != gp.end())
		{
			if ((*it).num == -1)
				gp.erase(it);
			else
				advance(it, 1);
		}
	}
	//for (size_t i = 0; i < gp.size() - 1; i++)
	//{
	//	int max_num = gp[i].num;
	//	int num = gp[i].num;
	//	int dir = gp[i].dir;
	//	for (size_t j = i + 1; j < gp.size(); j++)
	//	{
	//		if (!coincided[j] && gp[i].y == gp[j].y && gp[i].x == gp[j].x)
	//		{
	//			coincided[j] = true;
	//			if (max_num < gp[j].num)
	//			{
	//				max_num = gp[j].num;
	//				dir = gp[j].dir;
	//			}
	//			num += gp[j].num;
	//		}
	//	}
	//	gp[i].num = num;
	//	gp[i].dir = dir;
	//}

	//for (size_t i = 0; i < gp.size(); i++)
	//{
	//	if (coincided[i])
	//	{
	//		gp.erase(gp.begin() + i);
	//		coincided.erase(coincided.begin() + i);
	//	}
	//}
}

void move()
{
	for (auto it = gp.begin(); it != gp.end(); it++)
	{
		Microbe& m = *it;
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

		if (m.y == 0 || m.y == N - 1 || m.x == 0 || m.x == N - 1)
		{
			m.num /= 2;

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
	}
}

int main()
{
	ifstream cin("input.txt");
	int T;				// count of testcase
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		ans = 0;
		gp.clear();
		int y, x, num, dir;
		cin >> N >> M >> K;

		// input
		for (int i = 0; i < K; i++)
		{
			cin >> y >> x >> num >> dir;
			gp.push_back(Microbe(y, x, num, dir));
		}

		for (int i = 0; i < M; i++)
		{
			move();
			merge();
		}

		calculate();
		cout << '#' << test_case << ' ' << ans << endl;
	}

	return 0;
}
