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
    global N			    				# size of list
    global A							# To use global variable
    global N							# size of list
    global ONE_ARRAY						# one dimension array
    global TWO_ARRAY						# two dimension array

    A = int(input())						# To input value
    N = int(input())
    ONE_ARRAY = [0 for i in range(N)]                           # ONE_ARRAY initialization
    TWO_ARRAY = [[0 for col in range(N)] for row in range(N)]	# TWO_ARRAY initialization

    ''' Input '''
    # If the numbers are provided in same line,
    # First
    for i in range(N):
	    # map(<type>, input().split())
        y, x = map(int, input().split())

    # Second
    ONE_ARRAY = list(map(int, input().split()))
    
    # If the numbers are provided in different lines,
    # ONE_ARRAY = [ int(input()) for i in range(n)]

    ''' Output '''
    # print TWO_ARRAY
    # print has newline, thus newline is removed by print(<value>, end=' ')
    for i in range(N):
        for j in range(N):
            print(TWO_ARRAY[i][j], end=' ')
        print('')
    pass

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
