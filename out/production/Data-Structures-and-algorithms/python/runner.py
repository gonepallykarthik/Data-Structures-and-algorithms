    # @param A : list of integers
    # @param B : list of integers
    # @param C : list of integers
    # @param D : integer
    # @return an integer
from typing import List


def solve(A, B, C, D):
    if D == 0:
        return 0
    n = len(A)
    dp = [ [-1 for _ in range(D+1)] for _ in range(n) ]
    print(dp)
    return getMaxSweetness(n-1, D, A, B, C,dp)


def getMaxSweetness(idx, amount, A, B, C, dp):
    if idx == 0 and amount == 0:
        return 0
    
    if idx < 0 or amount < 0:
        return 0
    
    if dp[idx][amount] != -1:
        return dp[idx][amount]
    
    pick = float('-inf')
    if amount >= C[idx]:
        pick = A[idx] * B[idx] + getMaxSweetness(idx, amount-C[idx], A,B,C,dp)
    
    dontPick = 0 + getMaxSweetness(idx-1, amount, A, B, C, dp)
    # print((pick, dontPick))
    dp[idx][amount] =  max(pick, dontPick)
    return dp[idx][amount]

# print(solve([1,2,3], [2,2,10], [2,3,9], 8))

    # @param A : tuple of integers
	# @param B : tuple of integers
	# @param C : tuple of integers
	# @return an integer
def BirthdayParty( A, B, C):
    ans = 0

    value = max(A)
    dp = [-1] * (value+1)
    dp[0] = 0

    getMinCost(value, B, C, dp)
    for i in range(len(A)):
        ans += dp[A[i]]
    
    print(ans)
    return ans

def getMinCost(capacity, B, C, dp):
    if capacity == 0:
        return 0
    
    if dp[capacity] != -1:
        return dp[capacity]

    ans = float('inf')
    for i in range(len(B)):
        if capacity >= B[i]:
            # print(C[i] + getMinCost(capacity-B[i], B, C))
            ans = min(ans, C[i] + getMinCost(capacity-B[i], B, C, dp))
        
    dp[capacity] = ans
    return dp[capacity]


# BirthdayParty([2], [1], [2])

def training(activities):
    if len(activities) == 0:
        return 0
    n = len(activities[0])
    ans = float('-inf')
    rowLen = len(activities)
    for i in range(n):
        ans = max(ans, getMaxPoints(0, i, activities, rowLen-1))        

    return ans


def getMaxPoints(row, col, activities, n):
    if row == n:
        return activities[row][col]
    
    columnLen = len(activities[0])
    ans = 0
    for i in range(columnLen):
        points = 0
        if i != col:
            # print((row+1,col))
            points =  getMaxPoints(row+1, i, activities, n)
        ans = max(ans, activities[row][col] + points)
    return ans

activities = [
    [10,50,1],
    [5,100,11],
]

# print(training(activities))

def maxPath(matrix):
    if len(matrix) == 0:
        return 0
    n = len(matrix)
    m = len(matrix[0])
    ans = 0
    dp = [ [-1 for _ in range(m)] for _ in range(n) ]
    for i in range(m):
        ans = max(ans, helper(n-1, i, matrix, dp))
    
    print(ans)
    return ans
    

def helper(row, col, matrix, dp):
    if col >= len(matrix[0]) or col < 0:
        return float('-inf')
    
    if row == 0:
        return matrix[row][col]

    if dp[row][col] != -1:
        return dp[row][col]

    up = matrix[row][col] + helper(row-1,col, matrix, dp)   
    leftD = matrix[row][col] + helper(row-1, col-1, matrix, dp)
    rightD = matrix[row][col] + helper(row-1, col+1, matrix, dp)

    dp[row][col] = max(up, leftD, rightD)
    return dp[row][col]

matrix = [
    [1,2,10,4],
    [100,3,2,1],
    [1,1,20,2],
    [1,2,2,1]
]

# maxPath(matrix)

def knapsack2(A,B,C):
    maxValue = sum(A)
    n = len(A)
    print(maxValue)
    dp = [ [float('inf') for _ in range(maxValue+1)] for _ in range(n+1) ]
    dp[0][0] = 0

    for i in range(1, n+1):
        for j in range(maxValue):
            dp[i][j] = min(dp[i-1][j], B[i-1]+dp[i-1][j-A[i-1]])


    for i in range(maxValue, -1,-1):
        if dp[n][i] <= C:
            return i

# print(knapsack2([6,10,12], [10,20,30], 50))

def solve(nums):
    if len(nums) == 0:
        return 0
    dict = {0:1}
    ans = 0
    prefixSum = 0

    for i in range(len(nums)):
        prefixSum += nums[i]
        if prefixSum in dict:
            ans += dict[prefixSum]
        
        if prefixSum not in dict:
            dict[prefixSum] = 0
        
        dict[prefixSum] += 1
    
    print('a is ', ans)

# solve([6,-1,-3,4,-2,2,4,6,-12,-2])

def sumPossible(amount, nums):
    return sumHelper(amount, nums)

def sumHelper(amount, nums):
    if amount == 0:
        return 0
    if amount < 0:
        return float('inf')
    
    ans = float('inf')
    for num in nums:
        ans = min(ans,  1 + sumHelper(amount-num, nums))
    
    return ans

# print(sumPossible(5, [1,2,3]))
def nonAdjacentSum(nums):
    return nonAjacentHelper(len(nums)-1, nums)

def nonAjacentHelper(idx, nums):
    if idx == 0:
        return nums[0]
    
    if idx < 0:
        return 0
    
    pick = nums[idx] + nonAjacentHelper(idx-2, nums)
    dontPick = 0 + nonAjacentHelper(idx-1, nums)

    return max(pick, dontPick)

# print(nonAdjacentSum([2,4,5,12,7]))

def summingSquare(num):
    if num == 0:
        return 0
    return summingSquareHelper(num)

def summingSquareHelper(num):
    if num == 0:
        return 0
    
    if num < 0:
        return float('inf')

    ans = float('inf')
    for i in range(1, num+1):
        if num - (i*i) >= 0:
            ans = min(ans, 1 + summingSquareHelper(num-(i*i)))
    
    return ans

# print(summingSquare(12))

def closedIsland(grid: List[List[int]]) -> int:
    n = len(grid)
    m = len(grid[0])

    for row in range(n):
        if grid[row][0] == 0:
            Traversal(row,0,grid)

        if grid[row][m-1] == 0:
            Traversal(row, m-1, grid)

    for col in range(m):
        if grid[0][col] == 0:
            Traversal(0, col, grid)

        if grid[n-1][col] == 0:
            Traversal(n-1, col, grid)

    visited = [ [-1 for _ in range(m)] for _ in range(n) ] 
    ans = 0
    for row in  range(n):
        for col in range(m):
            if grid[row][col] == 0 and visited[row][col] == -1:
                ans += 1
                dfsTraversal(row, col, grid, visited)
    return ans

def dfsTraversal(row, col, grid, visited):
    n = len(grid)
    m = len(grid[0])

    visited[row][col] = 1
    dr = [-1,0,1,0]
    dc = [0,-1,0,1]
    for i in range(4):
        new_row = row + dr[i]
        new_col = col + dc[i]
        if new_row >=0 and new_row < n and new_col >=0 and new_col < m and grid[new_row][new_col] == 0 and visited[new_row][new_col] == -1:
            dfsTraversal(new_row, new_col, grid, visited)


def Traversal(row, col, grid):
    n = len(grid)
    m = len(grid[0])
    grid[row][col] = 2
    dr = [-1, 0, 1, 0]
    dc = [0, -1, 0, 1]

    for i in range(4):
        new_row = row + dr[i]
        new_col = col + dc[i]
        
        if new_row >=0 and new_row < n and new_col >=0 and new_col < m and grid[new_row][new_col] == 0:
            Traversal(new_row, new_col, grid)


grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
print(closedIsland(grid))


