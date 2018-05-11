#include <iostream>
#include <fstream>

using namespace std;

int K;					// count of number
int* num;				// array of lotto number
bool* visited_num;		// array of visited check for backtracking

void backtracking(int start, int n)
{
	if (n == 6)
	{
		for (int i = 0; i < K; i++)
			if (visited_num[i])
				cout << num[i] << " ";
		cout << endl;
		return;
	}

	for (int i = start; i < K; i++)
	{
		if (!visited_num[i])
		{
			visited_num[i] = true;
			backtracking(i + 1, n + 1);
		}
		visited_num[i] = false;
	}
}

int main()
{
	ifstream cin("input.txt");

	for (int test_case = 1; test_case <= 2; test_case++)
	//for (int test_case = 1; test_case <= 1; test_case++)
	{
		cin >> K;
		num = new int[K];
		visited_num = new bool[K];

		for (int i = 0; i < K; i++)
			cin >> num[i];
		fill_n(visited_num, K, false);

		backtracking(0, 0);

		delete[] num;
		delete[] visited_num;
		cout << endl;
	}

	return 0;
}