import sys
sys.stdin = open("input.txt", "r")

# define const global variables
DIR = [0, 1, 2, 3]
dy = [1, 0, -1, 0]
dx = [0, -1, 0, 1]

# class
class Coord:
    def __init__(self, y, x):	# define constructor
        self.y = y
        self.x = x
    pass

def init():
    global R			    # width of house
    global C			    # length of house
    global T			    # elapsed time
    global H			    # house array

    R, C, T = map(int, input().split())
    H = [[0 for col in range(C)] for row in range(R)]

    for i in range(R):
        H[i] = list(map(int, input().split()))

    for i in range(R):
        for j in range(C):
            print(H[i][j], end=' ')
        print('')
    pass

# def func():
#     global A, N			# To use global variables defined in 'init'
#     global DIR, dy, dx		# To use global variables globally

#     if (A is 0):
#     	print("A is 0")
#     elif (A is not 0):
#         print("A is not 0")
#     else:
#         print("A is nothing")

if __name__ == "__main__":
    init()
    pass
