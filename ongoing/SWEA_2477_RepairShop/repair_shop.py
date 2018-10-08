import sys
sys.stdin = open("input.txt", "r")

class Customer:
    def __init__(self, recep_num, maint_num):
        self.recep_num = recep_num
        self.maint_num = maint_num
    pass

global N                        # number of reception
global M                        # number of maintenance
global recep_occupied           # list of checking if occupied in reception
global maint_occupied           # list of checking if occupied in maintenance
global a                        # list of reception processing time
global b                        # list of maintenance processing time
global K                        # number of customer
global t                        # list of arrival time of customer
global A                        # lost reception window number
global B                        # lost maintenance window number
global customer_list            # list of customer
global finished                 # list for checking if finished

def init():
    global N, M, recep_occupied, maint_occupied, a, b, K, t, A, B, customer_list, finished

    N, M, K, A, B = map(int, input().split())
    t = [0 for i in range(K + 1)]
    a = [0 for i in range(N + 1)]
    b = [0 for i in range(M + 1)]
    recep_occupied = [False for i in range(N + 1)]
    maint_occupied = [False for i in range(M + 1)]
    finished = [False for i in range(K + 1)]
    customer_list = [Customer(0, 0) for i in range(K + 1)]
    
    a_list = input().split()
    b_list = input().split()
    for i in range(1, N + 1):
        a[i] = int(a_list[i - 1])
    
    for i in range(1, M + 1):
        b[i] = int(b_list[i - 1])
        
    t_list = input().split()
    for i in range(1, K + 1):
        t[i] = int(t_list[i - 1])
    pass

def allFinished():
    global K, finished
    
    for i in range(1, K + 1):
        if (not finished[i]):
            return False
    return True

def availRecepNum():
    global N, recep_occupied
    
    for i in range(1, N + 1):
        if (not recep_occupied[i]):
            return i
    return 0

def availMaintNum():
    global M, maint_occupied
    
    for i in range(1, M + 1):
        if (not maint_occupied[i]):
            return i
    return 0

def process():
    global N, M, recep_occupied, maint_occupied, a, b, K, t, A, B, customer_list, finished
    recep_waiting = []
    maint_waiting = []
    
    while (not allFinished()):
        for i in range(1, K + 1):
            if (not finished[i] and t[i] == 0):
                # reception not started
                if (customer_list[i].recep_num == 0):
                    avail_num = availRecepNum()
                    if (avail_num):
                        customer_list[i].recep_num = avail_num
                        recep_occupied[avail_num] = True
                        t[i] = a[avail_num]
                    else:
                        recep_waiting.append(i)
                
                # maintenance not started
                elif (customer_list[i].maint_num == 0):
                    recep_num = customer_list[i].recep_num
                    if (recep_waiting):
                        customer_list[recep_waiting].recep_num = recep_num
                    else:
                        recep_occupied[recep_num] = False
                        
                    
                    avail_num = availMaintNum()
                    if (avail_num):
                        customer_list[i].maint_num = avail_num
                        maint_occupied[avail_num] = True
                        t[i] = b[avail_num]
                    else:
                        maint_waiting.append(i)
                        
                # all finished
                else:
                    maint_num = customer_list[i].maint_num
                    if (maint_waiting):
                        customer_list[maint_waiting].maint_num = maint_num
                    else:
                        maint_occupied[maint_num] = False
                    
                    finished[i] = True
                
            elif (not finished[i] and t[i] != 0):
                t[i] -= 1
        
    pass
    
def findCustomer():
    global K, A, B, customer_list
    
    idx_sum = 0
    
    for i in range(1, K + 1):
        if (customer_list[i].recep_num == A and customer_list[i].maint_num == B):
            idx_sum += i
    
    return idx_sum if idx_sum != 0 else -1

    
if __name__ == '__main__':
    T = int(input())                # number of testcase
#     for test_case in range(1, T + 1):
    for test_case in range(2):
        init()
        process()
        ans = findCustomer()
        print("#%d %d" % (test_case, ans))
    pass