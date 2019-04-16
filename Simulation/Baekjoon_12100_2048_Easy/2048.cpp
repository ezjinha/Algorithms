#include <fstream>
#include <iostream>
using namespace std;

int N;                          // size of the board
int board[20][20];              // array of board
int copied_board[20][20];       // array of copied board
int dir_arr[5];                 // array of direction
const int DOWN  = 0;
const int LEFT  = 1;
const int UP    = 2;
const int RIGHT = 3;
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
int max_num;

void findMaxNum()
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            max_num = max_num < copied_board[i][j] ? copied_board[i][j] : max_num;
        }
    }
}

bool isInBoard(int y, int x)
{
    if ((y >= 0 && y < N) && (x >= 0 && x < N))
        return true;
    return false;
}

void getNumtoFront(int y, int x, int dir, int idx)
{
    for (size_t i = 0; i < N - idx - 1; i++)
    {
        int cy = y + dy[dir] * i;
        int cx = x + dx[dir] * i;
        int ny = y + dy[dir] * (i + 1);
        int nx = x + dx[dir] * (i + 1);

        int tmp(move(copied_board[cy][cx]));
        copied_board[cy][cx] = move(copied_board[ny][nx]);
        copied_board[ny][nx] = move(tmp);
    }
}

void addOrMove(int y, int x, int dir)
{
    int idx = 0;
    for (size_t i = 0; i < N; i++)
    {
        int cy = y + dy[dir] * idx;
        int cx = x + dx[dir] * idx;
        int ny = y + dy[dir] * (idx + 1);
        int nx = x + dx[dir] * (idx + 1);
        
        if (!isInBoard(ny, nx))
            break;

        if (copied_board[cy][cx] == 0)
        {
            getNumtoFront(cy, cx, dir, idx);
        }
        else
        {
            if (copied_board[ny][nx] == 0)
            {
                getNumtoFront(ny, nx, dir, idx + 1);
            }
            else
            {
                idx++;
                if (copied_board[cy][cx] == copied_board[ny][nx])
                {
                    copied_board[cy][cx] += copied_board[ny][nx];
                    copied_board[ny][nx] = 0;
                    getNumtoFront(ny, nx, dir, idx);
                }
            }
        }
    }
}

void moveBlock()
{
    for (size_t i = 0; i < 5; i++)
    {
        int dir = dir_arr[i];

        for (size_t j = 0; j < N; j++)
        {
            switch (dir)
            {
            case UP:
                addOrMove(0, j, UP);
                break;
            case RIGHT:
                addOrMove(j, N - 1, RIGHT);
                break;
            case DOWN:
                addOrMove(N - 1, j, DOWN);
                break;
            case LEFT:
                addOrMove(j, 0, LEFT);
                break;
            }
        }
    }
}

void copyBoard()
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            copied_board[i][j] = board[i][j];
        }
    }
}

void selectDirection(int idx, int num)
{
    if (num == 5)
    {
        copyBoard();
        moveBlock();
        findMaxNum();
        return;
    }

    for (size_t i = 0; i < 4; i++)
    {
        dir_arr[idx] = i;
        selectDirection(idx + 1, num + 1);
    }
}

int main()
{
    ifstream cin("input.txt");

    int T;                  // number of testcase
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++)
    {
            // input
            cin >> N;
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < N; j++)
                {
                    cin >> board[i][j];
                }
            }
            max_num = 0;

            selectDirection(0, 0);

            cout << max_num << endl;
    }
    
}