#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int W;					// width
int H;					// height
int N;					// count of intersection
int x1, y1, x2, y2;		// value of coordination
int ans;				// answer

void moveByMin()
{
	if ((y1 > y2) && (x1 < x2))				// Quadrant 1
		ans += (y1 - y2) + (x2 - x1);
	else if ((y1 > y2) && (x1 > x2))		// Quadrant 2
		ans += ((y1 - y2) > (x1 - x2) ? y1 - y2 : x1 - x2);
	else if ((y1 < y2) && (x1 > x2))		// Quadrant 3
		ans += (y2 - y1) + (x1 - x2);
	else if ((y1 < y2) && (x1 < x2))		// Quadrant 4
		ans += ((y2 - y1) > (x2 - x1) ? y2 - y1 : x2 - x1);
	else if (y1 == y2)						// X-axis
		ans += (x1 > x2 ? x1 - x2 : x2 - x1);
	else if (x1 == x2)						// Y-axis
		ans += (y1 > y2 ? y1 - y2 : y2 - y1);
}

int main()
{
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	int T;					// count of testcase
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		ans = 0;
		scanf("%d %d %d", &W, &H, &N);
		for (int i = 0; i < N - 1; i++)
		{
			if (i == 0)
				scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			else
			{
				y1 = y2;
				x1 = x2;
				scanf("%d %d", &x2, &y2);
			}
			moveByMin();
		}
		printf("#%d %d\n", test_case, ans);
	}

	return 0;
}