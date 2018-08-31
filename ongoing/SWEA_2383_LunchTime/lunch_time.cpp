#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Person
{
public:
	int y;
	int x;
	int time[2];	// taken time when stairs
	Person() {}
	Person(int _y, int _x) : y(_y), x(_x) {}
};

class Stairs
{
public:
	int y;
	int x;
	int l;		// stair length
	int n;		// number of people
	Stairs() {}
	Stairs(int _y, int _x, int _l) : y(_y), x(_x), l(_l), n(0) {}
};

// 1: person, x>=2: stairs
vector<Person> pv;	// person vector
vector<Stairs> sv;	// stairs vector
int room[10][10];	// array of room
int N;				// room length
int taken_time;		// taken time
int min_time;		// minimum taken time

void calculateTime()
{

}

void calculateDistance()
{
	for (size_t i = 0; i < pv.size(); i++)
	{
		for (size_t j = 0; j < sv.size(); j++)
		{
			int dis = abs(pv[i].y - sv[j].y) + abs(pv[i].x - sv[j].x);
			pv[i].time[j] = dis;
		}
	}
}

int main()
{
	ifstream cin("input.txt");
	int T;
	cin >> T;

	//for (int test_case = 1; test_case <= T; test_case++)
	for (int test_case = 1; test_case <= 1; test_case++)
	{
		pv.clear();
		sv.clear();
		//input
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> room[i][j];
				if (room[i][j] == 1)
					pv.push_back(Person(i, j));
				if (room[i][j] > 1)
					sv.push_back(Stairs(i, j, room[i][j]));
			}
		}

		calculateDistance();
	}

	return 0;
}