# # print('weclome1234')

# def subarray(nums):
#     if len(nums) == 0:
#         return 0

#     ans = 0
#     pref = { 0:0 }
#     curr = 0
#     for i in range()
    
#     return ans

from typing import List
import heapq


def colorful(A):
    if A == 0:
        return 0

    num = str(A)
    duplicates = set()
    
    # temp = A
    # while temp:
    #     r = temp % 10
    #     duplicates.add(r)
    #     temp = temp // 10
    
    # print(duplicates)
    # res = [ ]
    for i in range(len(num)):
        product = 1
        for j in range(i, len(num)):
            product *= int(num[j])
            if product in duplicates:
                return 0
            duplicates.add(product)

    return 1

print(colorful(23))



def sortArrayinGivenOrder(A, B):
    nums = {}
    for num in A:
        if num not in nums:
            nums[num] = 1
        else:
            nums[num] += 1
    
    res = []

    for num in B:
        pref = num
        if pref in nums:
            for _ in range(nums[num]):
                res.append(num)
            
            nums.pop(num)

    if len(nums) > 0:

        sorted_dict =dict(sorted(nums.items()))
        for k,v in sorted_dict.items():
            for _ in range(v):
                res.append(k)

    print(res)
    return res


# sortArrayinGivenOrder([5, 17, 100, 11],[1,100])

def deckRevealedIncreasing(deck: List[int]):
    if len(deck) == 0:
        return 0
    res = [0] * len(deck)
    deck.sort()
    n = len(deck)
    deckIdx = 0
    resIdx = 0
    skip = False
    
    visited = set()

    while deckIdx < n:
        if res[resIdx] == 0:
            
            # add it to card
            if skip == False:
                res[resIdx] = deck[deckIdx]
                deckIdx += 1
            
            # toggle skip
            skip = not skip

        resIdx = (resIdx + 1) % n
        # print(resIdx)

    return res

# deckRevealedIncreasing([17,13,11,2,3,5,7])

def countSubarrays(nums):
    if len(nums) == 0:
        return 0
    ans = 0
    left = 0
    dict = { }
    for right in range(len(nums)):
        currentNum = nums[right]
        if currentNum not in dict:
            dict[currentNum] = 1
        else:
            dict[currentNum] += 1
        print(dict)
        while left <= right and dict[currentNum] != 1:
            # shrink the window
            dict[nums[left]] -= 1
            left += 1

        ans += right-left + 1
    return ans

def isValid(counter : dict):
    for values in counter.values():
        if values > 1:
            return False
    return True


# print(countSubarrays([1,1,3]))

def lengthOfLongestSubstring(A):
    if len(A) == 0:
        return 0
    ans = 0
    left = 0
    duplicates = set()
    for right in range(len(A)):
        currentCharacter = A[right]
        
        while left<=right and currentCharacter in duplicates:
            duplicates.remove(A[left])
            left += 1

        duplicates.add(currentCharacter)
        ans = max(ans, right-left+1)


    return ans 

# print(lengthOfLongestSubstring("aabbac"))

def removeKdigits(num: str, k: int) -> str:
    stack = []
    for i in num:
        while stack and stack[-1] > i and k > 0:
            k -= 1
            stack.pop()
        if stack or i is not "0":
            print('exe')
            stack.append(i)
        
    if k:
        stack = stack[:-k]
    return ''.join(stack) or '0'

# print(removeKdigits("10001", 1))

def candiesDis(candies, num_people):
    if candies <=0 :
        return []

    people = [0] * num_people
    idx = 0
    totalCandies = candies
    cand = 1

    while totalCandies > 0:
    
        if totalCandies >= cand:
            people[idx] += cand
            totalCandies -= cand
            cand += 1
        else:
            people[idx] += totalCandies
            break
        print(cand)
        idx = (idx + 1) % num_people

    print(people)

# candiesDis(10,3)


A = "....x..xx...x."


pos = []
for i,character in enumerate(A):
    if character == "x":
        pos.append(i)

mid = len(pos) // 2
left = mid - 1
right = mid + 1
n = len(pos)
res = 0
k = 1
while left >=0:
    res += (pos[mid]- k - pos[left])
    print("for left ", pos[mid], k, pos[left])
    left -= 1
    k += 1

k = 1
while right < n:
    res += (pos[right] - pos[mid] - k)
    # print("for right is ", ans)
    right += 1
    k += 1

print(res)

def meetingRooms(rooms):
    if len(rooms) == 0 :
        return 0
    
    curr = 0
    max_rooms = 0
    times = []
    for room in rooms:
        start, end = room
        times.append( (start, 1) )
        times.append( (end, -1) )

    sorted_list = sorted(times, key=lambda x : x[0])
    
    for _,room in sorted_list:
        curr += room
        max_rooms = max(curr, max_rooms)
    print(max_rooms)

    
meetingRooms( [[0,30], [5,10], [15,20]] )
