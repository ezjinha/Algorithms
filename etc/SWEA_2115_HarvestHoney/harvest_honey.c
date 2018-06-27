#define _CRT_SECURE_NO_WARNINGS
typedef enum { false, true } bool;
#include <stdio.h>
#include <malloc.h>

int** hive;		// map of hive
int* selectedHive;	// array of selected hive
bool* selected;		// array of selected hive
int N;			// size of hive
int M;			// selective hive
int C;			// maximum honey amount
int hy, hx;		// harvested coordination
int max_profit;		// maximum profit
bool max_changed;	// check if max is changed

void emptyHive()
{
	for (int i = 0; i < M; i++)
	{
		hive[hy][hx + i] = -1;
	}
}

void findMax(int idx, int total, int profit)
{
	if (total > C)
		return;

	if (max_profit < profit)
	{
		max_changed = true;
		max_profit = profit;
	}	

	for (int i = idx; i < M; i++)
	{
		if (!selected[i])
		{
			selected[i] = true;
			total += selectedHive[i];
			profit += selectedHive[i] * selectedHive[i];
			findMax(idx + 1, total, profit);
			profit -= selectedHive[i] * selectedHive[i];
			total -= selectedHive[i];
			selected[i] = false;
		}
	}
}

void harvest()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - M + 1; j++)
		{
			bool isEmpty = false;
			for (int k = 0; k < M; k++)
			{
				selectedHive[k] = hive[i][j + k];
				if (selectedHive[k] == -1)
					isEmpty = true;
			}
			
			if (!isEmpty)
			{
				findMax(0, 0, 0);

				if (max_changed)
				{
					hy = i;
					hx = j;
					max_changed = false;
				}
			}
		}
	}
}

void input()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &hive[i][j]);
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;		// count of testcase
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	//for (int test_case = 1; test_case <= 2; test_case++)
	{
		max_profit = 0;
		scanf("%d %d %d", &N, &M, &C);

		// malloc
		hive = (int**)malloc(sizeof(int*) * N);
		for (int i = 0; i < N; i++)
			hive[i] = (int*)malloc(sizeof(int) * N);
		selectedHive = (int*)malloc(sizeof(int) * M);
		selected = (bool*)malloc(sizeof(bool) * M);
		for (int i = 0; i < M; i++)
			selected[i] = false;
		
		input();

		harvest();
		int first_max_profit = max_profit;
		max_profit = 0;
		emptyHive();
		harvest();

		printf("#%d %d\n", test_case, first_max_profit + max_profit);

		// free
		for (int i = 0; i < N; i++)
			free(hive[i]);
		free(hive);
		free(selectedHive);
		free(selected);
	}
	
	return 0;
}
