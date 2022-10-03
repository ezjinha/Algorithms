#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct _Node {
	int y;
	int x;
} Node;

int N;
int map[100][100];
Node home, company;
Node cust[10];
int visited[10];
int dist;

int abs(int num)
{
	return num >= 0 ? num : -num;
}

int getLength(Node departure, Node destination)
{
	return abs(departure.y - destination.y) + abs(departure.x - destination.x);
}

void visit(Node node, int num, int length)
{
	if (length > dist) return;
	if (num == N)
	{
		length += getLength(node, home);
		dist = dist > length ? length : dist;
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (visited[i] == 0)
		{
			visited[i] = 1;
			visit(cust[i], num + 1, length + getLength(node, cust[i]));
			visited[i] = 0;
		}
	}
}

void input()
{
	scanf("%d", &N);
	dist = 10000;

	scanf("%d %d", &company.x, &company.y);
	scanf("%d %d", &home.x, &home.y);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &cust[i].x, &cust[i].y);
		visited[i] = 0;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		input();
		visit(company, 0, 0);
		printf("#%d %d\n", test_case, dist);
	}

	return 0;
}