import sys
sys.stdin = open("input.txt", "r")

def init():
    global N                    # count of number
    global S                    # number set
    global max_cnt              # maximum count of set
    global ans                  # answer set
    
    N = int(input())
    S = [0 for i in range(N + 1)]
    for i in range(1, N + 1):
        S[i] = int(input())
    max_cnt = 0
    ans = []

    for num in S:
        print(num, end=" ")
    pass

def selectNum(idx, n):
    pass

if __name__ == "__main__":
    init()
    pass