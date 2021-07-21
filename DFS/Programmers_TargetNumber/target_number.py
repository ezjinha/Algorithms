import sys
sys.stdin = open("input.txt", "r")

def solution(numbers, target):
    if numbers == []:
        return 1 if target == 0 else 0
    else:
        return solution(numbers[1:], target + numbers[0]) + solution(numbers[1:], target - numbers[0])

def init():
    global numbers, target
    numbers = [int(num) for num in input().split()]
    target = int(input())

if __name__ == '__main__':
    init()
    print(solution(numbers, target))