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
#include <time.h>

#define LEFT  1
#define RIGHT 2
#define UP    3
#define DOWN  4

typedef enum { false, true } bool;

typedef struct
{
	int y;			// y-value
	int x;			// x-value
	int dir;		// direction
	int mem;		// memory value 0 ~ 15
} Loc;


int R;				// row
int C;				// column
char** ch;			// array of charcater
Loc** locArr;		// array for saving state of loc
bool isFinity;		// check if program is finity

bool isSameLoc(Loc* loc)
{
	if ((locArr[loc->y][loc->x].dir == loc->dir) &&
		(locArr[loc->y][loc->x].mem == loc->mem))
		return true;
	else
	{
		locArr[loc->y][loc->x].dir = loc->dir;
		locArr[loc->y][loc->x].mem = loc->mem;
		return false;
	}
}

void moveByDirection(Loc* loc)
{
	int y = loc->y;
	int x = loc->x;

	switch (loc->dir)
	{
	case LEFT:
		if (x == 0)
			loc->x = C - 1;
		else
			loc->x -= 1;
		break;
	case RIGHT:
		if (x == C - 1)
			loc->x = 0;
		else
			loc->x += 1;
		break;
	case UP:
		if (y == 0)
			loc->y = R - 1;
		else
			loc->y -= 1;
		break;
	case DOWN:
		if (y == R - 1)
			loc->y = 0;
		else
			loc->y += 1;
		break;
	}
}

void executeCmd(Loc loc)
{
	char cmd = ch[loc.y][loc.x];

	if (isSameLoc(&loc))
		return;

	switch (cmd)
	{
	case '<':
		loc.dir = LEFT;
		break;
	case '>':
		loc.dir = RIGHT;
		break;
	case '^':
		loc.dir = UP;
		break;
	case 'v':
		loc.dir = DOWN;
		break;
	case '_':
		if (loc.mem == 0)
			loc.dir = RIGHT;
		else
			loc.dir = LEFT;
		break;
	case '|':
		if (loc.mem == 0)
			loc.dir = UP;
		else
			loc.dir = DOWN;
		break;
	case '?':
		srand((unsigned int)time(NULL));
		loc.dir = rand() % 4 + 1;
		break;
	case '.':
		break;
	case '@':
		isFinity = true;
		return;
	case '0':
		loc.mem = 0;
		break;
	case '1':
		loc.mem = 1;
		break;
	case '2':
		loc.mem = 2;
		break;
	case '3':
		loc.mem = 3;
		break;
	case '4':
		loc.mem = 4;
		break;
	case '5':
		loc.mem = 5;
		break;
	case '6':
		loc.mem = 6;
		break;
	case '7':
		loc.mem = 7;
		break;
	case '8':
		loc.mem = 8;
		break;
	case '9':
		loc.mem = 9;
		break;
	case '+':
		if (loc.mem == 15)
			loc.mem = 0;
		else
			loc.mem += 1;
		break;
	case '-':
		if (loc.mem == 0)
			loc.mem = 15;
		else
			loc.mem -= 1;
		break;
	}

	moveByDirection(&loc);
	executeCmd(loc);
}

bool isThereAtSign()
{
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (ch[i][j] == '@')
				return true;
	return false;
}

void input()
{
	char br;		// line break
	for (int i = 0; i < R; i++)
	{
		scanf("%c", &br);
		for (int j = 0; j < C; j++)
		{
			scanf("%c", &ch[i][j]);
			memset(&locArr[i][j], 0, sizeof(locArr[i][j]));
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;			// count of testcase
	scanf("%d", &T);

	//for (int test_case = 1; test_case <= T; test_case++)
	for (int test_case = 1; test_case <= 2; test_case++)
	{
		scanf("%d %d", &R, &C);

		// malloc
		ch = (char**)malloc(sizeof(char*) * R);
		locArr = (Loc**)malloc(sizeof(Loc*) * R);
		for (int i = 0; i < R; i++)
		{
			ch[i] = (char*)malloc(sizeof(char) * C);
			locArr[i] = (Loc*)malloc(sizeof(Loc) * C);
		}

		isFinity = false;
		input();

		if (isThereAtSign())
		{
			Loc loc = { 0, 0, RIGHT, 0 };
			executeCmd(loc);
		}

		printf("#%d %s\n", test_case, isFinity ? "YES" : "NO");

		// free
		for (int i = 0; i < R; i++)
		{
			free(ch[i]);
			free(locArr[i]);
		}
		free(ch);
		free(locArr);
	}

	return 0;
}