import sys
sys.stdin = open("input.txt", "r")

def init():
    global N            # count of number
    global A            # list of number
    global OP           # list of count of operation (OP[0]:Plus, OP[1]:Minus, OP[2]:Multiply, OP[3]:divide)
    global min_num      # min value
    global max_num      # max value

    N = int(input())
    A = [0 for i in range(N)]
    OP = [0 for i in range(4)]

    A = list(map(int, input().split()))
    OP = list(map(int, input().split()))
    min_num = 1<<30
    max_num = -1<<30
    pass

def operate(result, idx, plus, minus, mul, div):
    global min_num, max_num
    if (idx == N - 1):
        min_num = result if result < min_num else min_num
        max_num = result if result > max_num else max_num
    else:
        if (plus != 0):
            operate(result + A[idx + 1], idx + 1, plus - 1, minus, mul, div)
        if (minus != 0):
            operate(result - A[idx + 1], idx + 1, plus, minus - 1, mul, div)
        if (mul != 0):
            operate(result * A[idx + 1], idx + 1, plus, minus, mul - 1, div)
        if (div != 0):
            operate(int(result / A[idx + 1]), idx + 1, plus, minus, mul, div - 1)
    pass

if __name__ == "__main__":
    for i in range(3):
        init()
        operate(A[0], 0, OP[0], OP[1], OP[2], OP[3])
        print(max_num)
        print(min_num)
    pass