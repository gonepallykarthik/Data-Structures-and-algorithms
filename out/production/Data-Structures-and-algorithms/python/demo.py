print('welcome to this application')

def meeting(rooms):
    if len(rooms) == 0:
        return True

    rooms.sort()
    print(rooms)
    prev_start, prev_end = rooms[0]
    
    for i in range(1, len(rooms)):
        current_start, current_end = rooms[i]
        if current_start < prev_end :
            return False
        else:
            prev_start = current_start
            prev_end = current_end
    
    return True

# print(meeting([[0,8],[8,10], [15,20]]))

def minWaitingTime(queries):
    if len(queries) == 0:
        return 0
    
    queries.sort()
    sum = queries[0]
    queries[0] = 0

    for i in range(1, len(queries)):
        temp = queries[i]
        queries[i] = sum
        sum += temp
    
    sum = 0
    for num in queries:
        sum +=num
    
    print(sum)

    # print(sum(queries))
    # res = sum(queries)
    # print(res)

minWaitingTime([3,2,1,2,6])


def tandemBicycle(redShirtSpeeds, blueShirtSpeeds, fastest):
    if len(redShirtSpeeds) != len(blueShirtSpeeds) :
        return 0
    
    if fastest:
        return getMaxSpeed(redShirtSpeeds, blueShirtSpeeds)
    
    return getMinSpeed(redShirtSpeeds, blueShirtSpeeds)


def getMaxSpeed(redShirtSpeeds, blueShirtSpeeds):
    max_speed = 0
    redShirtSpeeds.sort(reverse = True)
    blueShirtSpeeds.sort()

    for i in range(len(redShirtSpeeds)):
        max_speed += max(redShirtSpeeds[i], blueShirtSpeeds[i])

    return max_speed

def getMinSpeed(redShirtSpeeds, blueShirtSpeeds):
    min_speed = 0
    redShirtSpeeds.sort(reverse = True)
    blueShirtSpeeds.sort(reverse = True)

    for i in range(len(redShirtSpeeds)):
        min_speed += max(redShirtSpeeds[i], blueShirtSpeeds[i])

    return min_speed

print(tandemBicycle([5,5,3,9,2], [3,6,7,2,1], False))

import heapq
import math

def optimalFreelancing(jobs):
    # Write your code here.
    if len(jobs) == 0:
        return -1

    sorted_jobs = sorted(jobs, key=lambda x: x['deadline'])
    n = len(jobs)
    time = 0
    min_heap = []
    print(sorted_jobs)

    for i, job in enumerate(sorted_jobs):
        if time < job["deadline"] and time < 7:
            heapq.heappush(min_heap, job["payment"])
            time += 1
        else:
            topEle = min_heap[0]
            if job["payment"] > topEle:
                heapq.heappop(min_heap)
                heapq.heappush(min_heap, job["payment"])

    print(min_heap)

    sum = 0
    while len(min_heap) > 0:
        sum += min_heap[0]
        heapq.heappop(min_heap)

    return sum


jobs = [ 
    {
    "deadline": 1,
    "payment": 1
    },
    {
    "deadline": 2,
    "payment": 1
    },
    {
    "deadline": 3,
    "payment": 1
    },
    {
    "deadline": 4,
    "payment": 1
    },
    {
    "deadline": 5,
    "payment": 1
    },
    {
    "deadline": 6,
    "payment": 1
    },
    {
    "deadline": 7,
    "payment": 1
    },
    {
    "deadline": 8,
    "payment": 1
    },
    {
    "deadline": 9,
    "payment": 1
    },
    {
    "deadline": 10,
    "payment": 1
    }, ]


print(optimalFreelancing(jobs))

def calc(A, t):
    time = 0
    for i in range(len(A)):
        time += math.ceil( A[i] / t )
    return time


def solve(A, B):
    if len(A) == 0:
        return 0
    
    ans = float('inf')
    left = 1
    right = B 
    while left <= right:
        mid = left + (right-left) // 2
        print("m is ", mid)
        time = calc(A, mid)
        print('time is ', time)
        if time > B:
            left = mid + 1
        else:
            ans = min(ans, mid)
            right = mid - 1
    
    return ans


# solve([1,3,2,6], 4)

"""
special cases 
1-> CD,CM
2-> XL, XC
3-> IV, IX

"""


def romanToInteger(str):
    if len(str) == 0:
        return 0
    n = len(str)
    dict = { "I":1, "IV":4, "V":5, "IX":9, "X":10, "XL":40, "L":50, "XC":90, "C":100, "CD":400, "D":500, "CM":900, "M":1000}
    
    sum = 0
    i = 0
    while i < len(str):
        currentstr = str[i]

        # starts with "C"
        if ( i != n-1 and currentstr == "C" and (str[i+1] == 'D' or str[i+1] == 'M') ):
            currentstr += str[i+1]
            sum += dict[currentstr]
            i += 2
        
        # starts with "X"
        elif ( i != n-1 and currentstr == "X" and (str[i+1] == 'L' or str[i+1] == 'C') ):
            currentstr += str[i+1]
            sum += dict[currentstr]
            i += 2
        
        # starts with "I"
        elif ( i != n - 1 and  currentstr == "I" and (str[i+1] == 'V' or str[i+1] == 'X') ):
            currentstr += str[i+1]
            sum += dict[currentstr]
            i += 2
        
        else:
            sum += dict[currentstr]
            i += 1
    
    return sum


# print(romanToInteger("MCMXCIV"))

def intToRoman(num: int) -> str:
    if num == 0:
        return ""
    
    symbols = [ {"I": 1},
    {"IV": 4},
    {"V": 5},
    {"IX": 9},
    {"X": 10},
    {"XL": 40},
    {"L": 50},
    {"XC": 90},
    {"C": 100},
    {"CD": 400},
    {"D": 500},
    {"CM": 900},
    {"M": 1000} ]
    
    symbols_2d = [[key, value] for symbol in symbols for key, value in symbol.items()]

    res = ""
    for sym, val in reversed(symbols_2d):
        if num // val:
            count = num // val
            res += (sym*count)
            num = num % val

    print(res)
    


intToRoman(3)

dict ={ 0:[3,2,2], -2:[0], 1:[4], -1:[1]  }

sorted_dict = sorted(dict.items());
res = []

for key,value in sorted_dict:
    if len(value) > 2:
        print('inner block exe')
        value[1:] = sorted(value[1:])
        res.append(value)
    else:
        res.append(value)

# print(res)

def maxProductItself(nums):
    if len(nums) == 0:
        return 0
    
    res = max(nums)
    currMax = 1
    currMin = 1
    for num in nums:
        if num == 0:
            currMax = 1
            currMin = 1
            continue
        
        temp = num*currMax
        currMax = max(num*currMax, num*currMin, num)
        currMin = min(temp, num*currMin, num)
        res = max(res, currMax)
    
    return res

print(maxProductItself([-3,0,-5,0]))