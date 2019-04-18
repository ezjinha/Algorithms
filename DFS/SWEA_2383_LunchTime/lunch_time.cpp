#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Person
{
public:
	int y;
	int x;
	int selected_stairs;		// selected stairs
	int distance;				// distance from selected stairs or arrival
	bool isOnStairs;			// flag to check if the person is on stairs
	bool arrived;				// flag to check if the person arrived
	Person() {}
	Person(int _y, int _x) : y(_y), x(_x), selected_stairs(0), distance(0), isOnStairs(false), arrived(false) {}
};

class Stairs
{
public:
	int y;
	int x;
	int l;						// stair length
	int n;						// number of people
	Stairs() {}
	Stairs(int _y, int _x, int _l) : y(_y), x(_x), l(_l), n(0) {}
};

// 1: person, x>=2: stairs
vector<Person> pv;				// person vector
vector<Stairs> sv;				// stairs vector
int room[10][10];				// array of room
int N;							// room length
int min_time;					// minimum taken time

void getPersonToFront()
{
	int idx = 0;
	for (size_t i = 0; i < pv.size(); i++)
	{
		if (pv[i].isOnStairs)
		{
			swap(pv[idx], pv[i]);
			idx++;
		}
	}
}

/***************************************************************************/
// case to be considered
// When waiting in front of the stairs: distance == 0 && isOnStairs == false
// When arriving at first floor       : distance == 0 && isOnStairs == true
/***************************************************************************/
void move()
{
	int t = 0;
	bool areAllFinished = false;
	while (!areAllFinished)
	{
		areAllFinished = true;
		getPersonToFront();

		for (size_t i = 0; i < pv.size(); i++)
		{
			const int& selected_stairs = pv[i].selected_stairs;
			int& distance = pv[i].distance;
			bool& isOnStairs = pv[i].isOnStairs;
			bool& arrived = pv[i].arrived;

			if (!arrived)
			{
				// go to the stairs or go down stairs
				distance -= 1;

				// arrived at the stairs
				if (distance <= 0 && isOnStairs == false)
				{
					// the stairs is not full
					if (sv[selected_stairs].n < 3)
					{
						sv[selected_stairs].n += 1;															// increase number of person on stairs
						distance =  distance < 0 ? sv[selected_stairs].l : sv[selected_stairs].l + 1;		// add 1 minute when arriving at the stairs
						isOnStairs = true;
					}
				}

				if (distance == 0 && isOnStairs == true)
				{
					sv[selected_stairs].n -= 1;
					arrived = true;
				}
			}

			// check if all people have arrived
			areAllFinished &= arrived;
		}
		
		t++;
	}

	// calculate minimum elpased time
	min_time = min_time > t ? t : min_time;
}

void setPersonValue()
{
	for (Person& p : pv)
	{
		const int& sy = sv[p.selected_stairs].y;
		const int& sx = sv[p.selected_stairs].x;
		p.distance = abs(p.y - sy) + abs(p.x - sx);															// elapse 1 minute
		p.isOnStairs = false;
		p.arrived = false;
	}
}

void selectStairs(int idx, int num)
{
	if (num == pv.size())
	{
		setPersonValue();
		move();
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		pv[idx].selected_stairs = i;
		selectStairs(idx + 1, num + 1);
	}
}

int main()
{
	ifstream cin("input.txt");
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	// for (int test_case = 1; test_case <= 1; test_case++)
	{
		pv.clear();
		sv.clear();
		min_time = 1 << 30;
		//input
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> room[i][j];
				if (room[i][j] == 1)
					pv.emplace_back(i, j);
				if (room[i][j] > 1)
					sv.emplace_back(i, j, room[i][j]);
			}
		}

		selectStairs(0, 0);
		cout << '#' << test_case << ' ' << min_time << endl;
	}

	return 0;
}
