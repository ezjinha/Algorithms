#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef enum { false, true } bool;

#define STAY  0
#define UP    1
#define RIGHT 2
#define DOWN  3
#define LEFT  4

int dy[] = { 0, -1, 0, 1, 0 };
int dx[] = { 0, 0, 1, 0, -1 };

typedef struct
{
	int y;
	int x;
} User;

typedef struct
{
	int y;
	int x;
	int c;					// coverage
	int p;					// performance
} BC;

int map[10][10];				// array of map
int M;						// move time
int A;						// number of Battery Charger
int move_info_A[100];				// move info of A
int move_info_B[100];				// move info of B
BC bc[8];					// array of BC
int max_charge;					// max value of charge

void sumCharge(User a, User b, int t, int charge_sum)
{
	if (t == M + 1)
	{
		max_charge = charge_sum;
		return;
	}
	
	// sum charge
	int sum_A = 0;
	int sum_B = 0;
	int max_sum_A = 0;
	int max_sum_B = 0;
	int max_sum = 0;

	if ((map[a.y][a.x] & map[b.y][b.x]) != 0)
	{
		for (int i = 0; i < A; i++)
		{
			sum_A = ((map[a.y][a.x] & (1 << i)) >> i) * bc[i].p;
			max_sum_A = max_sum_A < sum_A ? sum_A : max_sum_A;


			for (int j = 0; j < A; j++)
			{
				sum_B = ((map[b.y][b.x] & (1 << j)) >> j) * bc[j].p;
				max_sum_B = max_sum_B < sum_B ? sum_B : max_sum_B;

				if (((map[a.y][a.x] & (1 << i)) >> i) == 1 && 
					((map[b.y][b.x] & (1 << j)) >> j) == 1 &&
					i == j)
				{
					max_sum = max_sum < sum_B ? sum_B : max_sum;
				}
				else
					max_sum = max_sum < sum_A + sum_B ? sum_A + sum_B : max_sum;
			}
		}
	}
	else
	{
		for (int i = 0; i < A; i++)
		{
			sum_A = ((map[a.y][a.x] & (1 << i)) >> i) * bc[i].p;
			sum_B = ((map[b.y][b.x] & (1 << i)) >> i) * bc[i].p;
			max_sum_A = max_sum_A < sum_A ? sum_A : max_sum_A;
			max_sum_B = max_sum_B < sum_B ? sum_B : max_sum_B;
		}

		max_sum = max_sum_A + max_sum_B;
	}

	// move
	int move_info_a = move_info_A[t];
	int move_info_b = move_info_B[t];
	a.y += dy[move_info_a];
	a.x += dx[move_info_a];
	b.y += dy[move_info_b];
	b.x += dx[move_info_b];

	sumCharge(a, b, t + 1, max_sum + charge_sum);
}

void setCharge(int y, int x, int bc_idx, int idx, int c)
{
	if (idx == c)
		return;

	if ((map[y][x] & (1 << bc_idx)) >> bc_idx == 0)
		map[y][x] += 1 << bc_idx;

	for (int i = 1; i <= 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny >= 0 && ny < 10 && nx >= 0 && nx < 10)
			setCharge(ny, nx, bc_idx, idx + 1, c);
	}
}

void setChargeArea()
{
	for (int i = 0; i < A; i++)
	{
		int y = bc[i].y;
		int x = bc[i].x;
		int c = bc[i].c;
		setCharge(y, x, i, 0, c);
	}
}

void input()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			map[i][j] = 0;

	scanf("%d %d", &M, &A);
	for (int i = 0; i < M; i++)
		scanf("%d", &move_info_A[i]);
	for (int i = 0; i < M; i++)
		scanf("%d", &move_info_B[i]);
	for (int i = 0; i < A; i++)
	{
		int x, y, c, p;
		scanf("%d %d %d %d", &x, &y, &c, &p);
		bc[i].y = y - 1;
		bc[i].x = x - 1;
		bc[i].c = c + 1;
		bc[i].p = p;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		input();
		setChargeArea();
		User a = { 0, 0 };
		User b = { 9, 9 };
		sumCharge(a, b, 0, 0);

		printf("#%d %d\n", test_case, max_charge);
	}

	return 0;
}
