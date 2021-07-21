import sys
sys.stdin = open("input.txt", "r")

def init():
    global N                    # count of number
    global S                    # number set
    global visited              # list of checking if visited
    global max_cnt              # maximum count of set
    global ans                  # answer set
    
    N = int(input())
    S = [0 for i in range(N + 1)]
    visited = [False for i in range(N + 1)]
    ans = [False for i in range(N + 1)]
    for i in range(1, N + 1):
        S[i] = int(input())
    max_cnt = 0
    pass

def selectNum(v, idx, n):
    global max_cnt, ans
    if v == idx:
        max_cnt = n if max_cnt < n else max_cnt
        pass
    elif n == N:
        pass
    else:
        for i in range(1, N + 1):
            v = i if n == 0 else v
            if not visited[i]:
                visited[i] = True
                selectNum(v, S[i], n + 1)
                visited[i] = False
        pass
    pass

if __name__ == "__main__":
    init()
    selectNum(0, 1, 0)
    print(max_cnt)
    pass