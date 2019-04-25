import sys
sys.stdin = open("input.txt", "r")

# define const global variables
DIR = [0, 1, 2, 3]
dy = [1, 0, -1, 0]
dx = [0, -1, 0, 1]

# class
class Coord:
    def __init__(self, y, x):					# define constructor
        self.y = y
	self.x = x
    pass

def init():
    global A							# To use global variable
    global N							# size of list
    global ONE_ARRAY						# one dimension array
    global TWO_ARRAY						# two dimension array

    A = int(input())						# To input value
    N = int(input())
    ONE_ARRAY = [0 for i in range(N)]
    TWO_ARRAY = [[0 for col in range(N)] for row in range(N)]	# initialization

    for i in range(N):
        # number of variable in one row in 'input.txt'
	# map(<type>, input().split())
        y, x = map(int, input().split())

def func():
    global A, N							# To use global variables defined in 'init'
    global DIR, dy, dx						# To use global variables globally

    if (A is 0):
    	print("A is 0")
    elif (A is not 0):
        print("A is not 0")
    else:
        print("A is nothing")

if __name__ == "__main__":
    init()
    func()
    pass
