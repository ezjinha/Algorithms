/*
문자	수행 명령
<	이동 방향을 왼쪽으로 바꾼다.
>	이동 방향을 오른쪽으로 바꾼다.
^	이동 방향을 위쪽으로 바꾼다.
v	이동 방향을 아래쪽으로 바꾼다.
_	메모리에 0이 저장되어 있으면 이동 방향을 오른쪽으로 바꾸고, 아니면 왼쪽으로 바꾼다.
|	메모리에 0이 저장되어 있으면 이동 방향을 아래쪽으로 바꾸고, 아니면 위쪽으로 바꾼다.
?	이동 방향을 상하좌우 중 하나로 무작위로 바꾼다. 방향이 바뀔 확률은 네 방향 동일하다.
.	아무 것도 하지 않는다.
@	프로그램의 실행을 정지한다.
0~9	메모리에 문자가 나타내는 값을 저장한다.
+	메모리에 저장된 값에 1을 더한다. 만약 더하기 전 값이 15이라면 0으로 바꾼다.
-	메모리에 저장된 값에 1을 뺀다. 만약 빼기 전 값이 0이라면 15로 바꾼다.
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