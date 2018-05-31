/*
����	���� ���
<	�̵� ������ �������� �ٲ۴�.
>	�̵� ������ ���������� �ٲ۴�.
^	�̵� ������ �������� �ٲ۴�.
v	�̵� ������ �Ʒ������� �ٲ۴�.
_	�޸𸮿� 0�� ����Ǿ� ������ �̵� ������ ���������� �ٲٰ�, �ƴϸ� �������� �ٲ۴�.
|	�޸𸮿� 0�� ����Ǿ� ������ �̵� ������ �Ʒ������� �ٲٰ�, �ƴϸ� �������� �ٲ۴�.
?	�̵� ������ �����¿� �� �ϳ��� �������� �ٲ۴�. ������ �ٲ� Ȯ���� �� ���� �����ϴ�.
.	�ƹ� �͵� ���� �ʴ´�.
@	���α׷��� ������ �����Ѵ�.
0~9	�޸𸮿� ���ڰ� ��Ÿ���� ���� �����Ѵ�.
+	�޸𸮿� ����� ���� 1�� ���Ѵ�. ���� ���ϱ� �� ���� 15�̶�� 0���� �ٲ۴�.
-	�޸𸮿� ����� ���� 1�� ����. ���� ���� �� ���� 0�̶�� 15�� �ٲ۴�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int R;				// row
int C;				// column
char** ch;			// array of charcater

void executeCmd()
{
	char cmd = '\0';
	switch (cmd)
	{
	case '<':
		break;
	case '>':
		break;
	case '^':
		break;
	case 'v':
		break;
	case '_':
		break;
	case '|':
		break;
	case '?':
		break;
	case '.':
		break;
	case '@':
		break;
	case '0':
		break;
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '7':
		break;
	case '8':
		break;
	case '9':
		break;
	case '+':
		break;
	case '-':
		break;
	}
}

void input()
{
	char br;		// line break
	for (int i = 0; i < R; i++)
	{
		scanf("%c", &br);
		for (int j = 0; j < C; j++)
			scanf("%c", &ch[i][j]);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;			// count of testcase
	scanf("%d", &T);

	//for (int test_case = 1; test_case <= T; test_case++)
	for (int test_case = 1; test_case <= 1; test_case++)
	{
		scanf("%d %d", &R, &C);

		// malloc
		ch = (char**)malloc(sizeof(char*) * R);
		for (int i = 0; i < R; i++)
			ch[i] = (char*)malloc(sizeof(char) * C);

		input();

		// free
		for (int i = 0; i < R; i++)
			free(ch[i]);
		free(ch);
	}

	return 0;
}