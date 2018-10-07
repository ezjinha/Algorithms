import sys
sys.stdin = open("input.txt", "r")
import collections

DOWN   = 0
LEFT   = 1
UP     = 2
RIGHT  = 3
DIR = [0, 1, 2, 3]
dy = [1, 0, -1, 0]
dx = [0, -1, 0, 1]

class Coord:
    def __init__(self, y, x):
        self.y = y
        self.x = x
    pass

class Cmd:
    def __init__(self, t, c):
        self.t = t
        self.c = c
    pass

def init():
    global N            # size of board
    global K            # number of apple
    global board        # board array
    global L            # number of cmd
    global cmd_list     # cmd array
    global snake        # snake array

    N = int(input())
    board = [[0 for col in range(N)] for row in range(N)]

    K = int(input())
    for i in range(K):
        y, x = map(int, input().split())
        board[y - 1][x - 1] = 2             # apple

    L = int(input())
    cmd_list = collections.deque()
    for i in range(L):
        t, c = map(str, input().split())
        cmd_list.append(Cmd(int(t), c))

    snake = collections.deque()
    snake.append(Coord(0, 0))
    board[0][0] = 1

def move():
    global N, K, board, L, cmd_list, snake
    global DOWN, LEFT, UP, RIGHT, DIR, dy, dx

    dir = RIGHT             # init direction
    t = 0                   # init time

    while (True):
        t += 1
        y = snake[0].y
        x = snake[0].x
        ny = y + dy[dir]
        nx = x + dx[dir]

        if (isOver(ny, nx)):
            break

        if (board[ny][nx] is 0):
            tail = snake.pop()
            board[tail.y][tail.x] = 0

        board[ny][nx] = 1
        snake.appendleft(Coord(ny, nx))

        if (len(cmd_list) != 0 and t == cmd_list[0].t):
            c = cmd_list.popleft().c
            dir = changeDir(c, dir)

    print(t)


def isOver(y, x):
    global N, board
    if (y < 0 or y >= N or x < 0 or x >= N):
        return True
    elif (board[y][x] is 1):
        return True
    return False

def changeDir(c, dir):
    if (c is "D"):
        return dir + 1 if dir != 3 else 0
    else:       # c is "L"
        return dir - 1 if dir != 0 else 3

if __name__ == '__main__':
    T = int(input())        # number of testcase

    for test_case in range(1, T + 1):
        init()
        move()

    pass