#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fee[4];			// 0: 1day, 1: 1month, 2: 3months, 3: 1year
int day[12];			// swimming day of each month
int min_fee;			// minimum fee

void calculateFee(int month, int total)
{
	if (month >= 12)
	{
		min_fee = min_fee > total ? total : min_fee;
		return;
	}

	calculateFee(month + 1, total + fee[0] * day[month]);

	if (day[month] != 0)
	{
		calculateFee(month + 1, total + fee[1]);
		calculateFee(month + 3, total + fee[2]);
	}
}

void input()
{
	for (int i = 0; i < 4; i++)
		scanf("%d", &fee[i]);
	for (int i = 0; i < 12; i++)
		scanf("%d", &day[i]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;						// count of testcase
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		input();
		min_fee = fee[3];		// assum that 1 year fee is minimum
		calculateFee(0, 0);
		printf("#%d %d\n", test_case, min_fee);
	}

	return 0;
}
