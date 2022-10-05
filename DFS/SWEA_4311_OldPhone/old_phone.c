#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int M;			// touchable count
int N;			// touchable number
int O;			// touchable operator
int num[10];	// touchable number array
char op[4];		// touchable operator array
int W;			// wanted number
int min_cnt;	// minimum touch count

int best[1000];
int checked[1000];

int combCnt;
int comb[1000];
int combNumCnt[1000];
int combChecked[1000];

int calculateNum(int n1, char oper, int n2)
{
	switch (oper)
	{
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '*':
		return n1 * n2;
	case '/':
		return n1 / n2;
	}
}

void calNumDfs(int cnt, int sum)
{
	for (int i = 0; i < O; i++)
	{
		for (int j = 0; j < combCnt; j++)
		{
			int curNum = comb[j];
			int nCnt = cnt + combNumCnt[j] + 1;
			if (nCnt > M - 1) break;
			if (op[i] == '/' && curNum == 0) continue;

			int next = calculateNum(sum, op[i], curNum);

			if (op[i] == '+' && next > 999) break;
			if (op[i] == '-' && next < 0) break;
			if (op[i] == '*' && next > 999) break;
			if (checked[next] == 1) continue;
			if (nCnt >= best[next]) continue;

			best[next] = nCnt;
			checked[next] = 1;
			calNumDfs(nCnt, next);
			checked[next] = 0;
		}
	}
}

void init()
{
	for (int i = 0; i < 1000; i++)
	{
		best[i] = 99;
		checked[i] = 0;
	}

	for (int i = 0; i < combCnt; i++)
	{
		best[comb[i]] = combNumCnt[i];
	}
}

void combDfs(int cnt, int sum)
{
	for (int i = 0; i < N; i++)
	{
		int next = sum * 10 + num[i];
		if (next > 999) continue;
		if (cnt + 1 > M) continue;
		if (combChecked[next] != 0) continue;

		combChecked[next] = 1;
		combDfs(cnt + 1, next);
	}
}

void combineNum()
{
	for (int i = 0; i < 1000; i++)
	{
		comb[i] = 0;
		combNumCnt[i] = 0;
		combChecked[i] = 0;
	}

	combDfs(0, 0);

	combCnt = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (combChecked[i] == 0) continue;

		if (i < 10) combNumCnt[combCnt] = 1;
		else if (i < 100) combNumCnt[combCnt] = 2;
		else combNumCnt[combCnt] = 3;

		comb[combCnt] = i;
		combCnt++;
	}
}

void input()
{
	scanf("%d %d %d", &N, &O, &M);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &num[i]);
	}

	for (int i = 0; i < O; i++)
	{
		int operator;
		scanf("%d", &operator);
		switch (operator)
		{
		case 1:
			op[i] = '+';
			break;
		case 2:
			op[i] = '-';
			break;
		case 3:
			op[i] = '*';
			break;
		case 4:
			op[i] = '/';
			break;
		}
	}

	scanf("%d", &W);
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		input();
		combineNum(0, 0);
		init();
		if (best[W] == 99) {
			for (int i = 0; i < combCnt; i++)
			{
				calNumDfs(combNumCnt[i], comb[i]);
			}

			min_cnt = best[W] == 99 ? -1 : best[W] + 1;
		}
		else
		{
			min_cnt = best[W];
		}
		
		printf("#%d %d\n", test_case, min_cnt);
	}
	return 0;
}