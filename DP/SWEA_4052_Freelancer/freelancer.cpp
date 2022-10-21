#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;	// 1 <= n <= 500;
int m;  // 1 <= m <= 10000;

struct Task
{
	int s;	// start date
	int e;	// end date
	int c;	// cost

	bool operator<(const Task& task)
	{
		return e < task.e;
	}

	bool isConflicted(const Task& task)
	{
		return (s >= task.s && s <= task.e) || (e >= task.s && e <= task.e) || (s <= task.s && e >= task.e) || (s >= task.s && e <= task.e);
	}
};

vector<Task> task(500);
vector<int> cost(500);

int main()
{
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		cin >> n >> m;
		
		for (int i = 0; i < n; i++)
		{
			int s, e, c;
			cin >> s >> e >> c;
			task[i] = { s, e, c };
		}

		sort(task.begin(), task.begin() + n);

		cost[0] = task[0].c;
		for (int i = 1; i < n; i++)
		{
			if (task[i].isConflicted(task[i - 1]))
			{
				// find index that end date before start date of current task
				int idx = -1;
				for (int j = i - 1; j >= 0; j--)
				{
					if (task[j].e < task[i].s)
					{
						idx = j;
						break;
					}
				}

				if (idx == -1)
				{
					cost[i] = max(cost[i - 1], task[i].c);
				}
				else
				{
					cost[i] = max(cost[i - 1], cost[idx] + task[i].c);
				}
			}
			else
			{
				cost[i] = cost[i - 1] + task[i].c;
			}
		}

		cout << '#' << test_case << ' ' << cost[n - 1] << endl;
	}

	return 0;
}