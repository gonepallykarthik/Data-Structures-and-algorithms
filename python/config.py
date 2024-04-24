# print("hello welcome application")


"""
2163 -> 3 ways to decode
"""
def waysToDecode(str):
    if len(str) == 0:
        return 0 

    if len(str) == 1 and str[0] == '0':
        return 0
    
    n = len(str)
    dp = [0] * (n+1)
    dp[0] = 1
    dp[1] = 1

    for i in range(2, n+1):
        if int(str[i-1]) >=1 and int(str[i-1]) <= 9:
            dp[i] = dp[i-1]
        
        if int(str[i-2]) == 1:
            dp[i] += dp[i-2]
        elif int(str[i-2]) == 2 and int(str[i-1]) >=0 and int(str[i-1]) <= 6:
            dp[i] += dp[i-2]
    
    print(dp)
    return dp[n]


# print(waysToDecode("0799733"))
# print(waysToDecode("11"))

def minNumberOfCoinsForChangeHelper(n, denoms, dp):
    if n == 0: return 0
    # print(n)
    if dp[n] != -1: return dp[n]
    
    ans = float('inf')
    for denom in denoms:
        if denom <= n :
            ans = min(ans, minNumberOfCoinsForChangeHelper(n-denom, denoms, dp))
    
    dp[n] = 1 + ans
    return dp[n]


def minNumberOfCoinsForChange(n, denoms):
    # Write your code here.
    dp = [-1] * (n+1)
    print(dp)
    return minNumberOfCoinsForChangeHelper(n, denoms, dp)


# print(minNumberOfCoinsForChange(7,[1,5,10]))

def maxSubsetSumNoAdjacent(array):
    # Write your code here.
    if len(array) == 0:
        return 0
    dp = [0] * len(array)
    first = array[0]
    second = max(array[0], array[1])
    
    # dp[0] = array[0]
    # dp[1] = max(array[0], array[1])

    for i in range(2, len(array)):
        curr = max(second, first + array[i])
        dp[i] = curr
        first = second
        second = curr

    # print(dp)
    return second

# print(maxSubsetSumNoAdjacent([75,105,120,75,90,135]))


def uniquePaths(m: int, n: int) -> int:
    dp = [ [-1 for _ in range(n)] for _ in range(m)]
    
    for i in range(n):
        dp[0][i] = 1
    
    for i in range(m):
        dp[i][0] = 1

    for row in range(1, m):
        for col in range(1, n):
            dp[row][col] = dp[row-1][col] + dp[row][col-1]

    return dp[m-1][n-1]

uniquePaths(3,7)

"""
    0 -> marked as empty space 
    1 -> marked as obstacle
"""

def uniquePathsWithObstacles(A):
    if len(A) == 0:
        return 0

    m = len(A)
    n = len(A[0])

    for row in range(m):
        for col in range(n):
            A[row][col] = 1 if A[row][col] == 0 else 0

    
    dp = [ [-1 for _ in range(n)] for _ in range(m)]
    dp[0][0] = A[0][0]

    for i in range(1, n):
        if A[0][i] == 0:
            dp[0][i] = 0
        else:
            dp[0][i] = dp[0][i-1] 

    for i in range(1, m):
        if A[i][0] == 0:
            dp[i][0] = 0
        else:
            dp[i][0] = dp[i-1][0]

    for row in range(1, m):
        for col in range(1, n):
            if A[row][col] == 0:
                dp[row][col] = 0
            else:
                dp[row][col] = dp[row-1][col] + dp[row][col-1]


    return dp[m-1][n-1]

A = [
        [0, 0, 0],
        [1, 1, 1],
        [0, 0, 0]
    ]

# uniquePathsWithObstacles(A)

def catalanNumber(num):
    if num == 0: return 1
    if num == 1: return 1

    dp = [0] * (num+1)
    dp[0] = 1
    dp[1] = 1

    for i in range(2, num+1):
        for j in range(0, i):
            temp = dp[j]* dp[i-j-1]
            dp[i] += dp[j]* dp[i-j-1]
        

    print(dp)

# catalanNumber(4)


# [1, 5, -3, 4, -2]
def solve(A,B,C,D):
    if len(A) == 0:
        return 0
    
    prefixMax1 = [0] * len(A)
    for i in range(len(A)):
        if i == 0:
            prefixMax1[i] = A[i] * B
        else:
            prefixMax1[i] = max(prefixMax1[i-1], A[i]*B)
    
    prefixMax2 = [0] * len(A)
    for i in range(len(A)):
        if i == 0:
            prefixMax2[i] = A[i] * C + prefixMax1[i]
        else:
            prefixMax2[i] = max(prefixMax2[i-1], A[i]*C+prefixMax1[i])

    prefixMax3 = [0] * len(A)
    for i in range(len(A)):
        prefixMax3[i] = A[i] * D + prefixMax2[i]
    
    return max(prefixMax3)

# print(solve([3,2,1], 1, -10, 3))


def minPathSum(row, col, grid, dp):
    if row == 0 and col == 0:
        return grid[row][col]

    if dp[row][col] != -1:
        return dp[row][col]

    if row < 0 or col < 0 :
        return float('inf')

    
    up = grid[row][col] + minPathSum(row-1, col, grid)
    left = grid[row][col] + minPathSum(row, col-1, grid)
    
    dp[row][col] =  min(up, left)
    return dp[row][col]


grid = [
    [1, -3, 2],
    [2, 5, 10],
    [5, -5, 1]
    ]

# print(minPathSum(2,2,grid))

def calculateMinimumHP(A):
    if len(A) == 0:
        return 0
    r = len(A)
    c = len(A[0])
    dp = [ [-1 for _ in range(c+1)] for _ in range(r+1) ]
    
    return minimumHP(0, 0, A, dp, r, c)


def minimumHP(row, col, grid, dp, n, m):
    if row == n-1 and col == m-1:
        return max(1, 1-grid[row][col])
    
    if dp[row][col] != -1 :
        return dp[row][col]
    
    if row >= n or col >= m :
        return float('inf')
    
    dp[row][col] = max( min(minimumHP(row+1,col,grid,dp,n,m), minimumHP(row,col+1,grid,dp,n,m))-grid[row][col] , 1)

    return dp[row][col]


matrix = [
    [1, -1, 0],
    [-1, 1, -1],
    [1, 0, -1]
]

print(calculateMinimumHP(matrix))
