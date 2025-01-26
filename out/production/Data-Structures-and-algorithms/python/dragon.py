
from typing import List


def minPathSuminTriangle(triangle):
    if len(triangle) == 0:
        return 0
    rows = len(triangle)
    cols = len(triangle[-1])
    dp = [ [-1 for _ in range(cols)] for _ in range(rows) ]
    last_row_idx = rows-1 
    
    last_col_idx = float('inf')
    min_ele = float('inf')
    # get Min element of last row
    for i, num in enumerate(triangle[-1]):
        if num < min_ele:
            last_col_idx = i
            min_ele = num

    min_sum = float('inf')
    for i in range(len(triangle[rows-1])):
        min_sum = min(min_sum, calMinPathSum(rows-1, i, triangle, dp))
    # print(last_row_idx, last_col_idx)
    print(min_sum)
    return min_sum

#  start -> 0,0
def calMinPathSum(row, col, triangle, dp):
    if row == 0:
        return triangle[0][0]

    if row < 0 or col < 0 or col >= len(triangle[row]):
        return float('inf')

    if dp[row][col] != -1:
        return dp[row][col]
    
    up = triangle[row][col] + calMinPathSum(row-1, col, triangle,dp)
    left = triangle[row][col] + calMinPathSum(row-1,col-1,triangle, dp)

    dp[row][col] = min(up,left)
    return dp[row][col]

tri = [ [2],
    [6, 6],
    [7,8,4],
    ]

# tri = [ [1] ]

# print(minPathSuminTriangle(tri))

def maximalRectangle(A):
    if len(A) == 0:
        return 0
    
    for row in range(len(A)):
        for col in range(len(A[0])):
            if col == 0:
                continue
            if A[row][col] == 0:
                continue
            else:
                if A[row][col-1] >= 1:
                    A[row][col] = 1 + A[row][col-1]
                else:
                    A[row][col] = 1

    max_area = float('-inf')
    for row in range(len(A)):
        for col in range(len(A[0])):
            area = calculateHeight(row,col,A)
            # print('area of ', (row,col) , 'is' ,  area)
            max_area = max(max_area, area)
    
    return max_area


def calculateHeight(row, col, A):
    if A[row][col] == 0:
        return 0
    
    area = 0
    height = 1
    width = A[row][col]
    area = max(area, height * width)

    i = row - 1
    
    while i >= 0:
        if A[i][col] == 0:
            break
        width = min(width, A[i][col])
        height += 1
        area = max(area, height * width )
        i -= 1

    return area


matrix = [
       [0, 1, 0],
       [1, 1, 1]
     ]
# print(maximalRectangle(matrix))


def reverseLevelOrderTraversal(root):
    if root is None:
        return None
    
    nodes = [ ]
    queue = [ root ]
    while len(queue) > 0:
        node = []
        for i in range(len(queue)):
            frontEle = queue.pop(0)
            node.append(frontEle.val)
            if frontEle.left != None:
                queue.append(frontEle.left)
            
            if frontEle.right != None:
                queue.append(frontEle.right)
        nodes.append(node)

    res  = []
    for ls in reversed(nodes):
        res.extend(ls)
    
    return res


def rightViewTree(root):
    if root is None:
        return None
    ds = [ ]
    Traversal(root,0,ds)
    return ds

def Traversal(root, level, ds):
    if root is None:
        return
    
    if level == len(ds):
        ds.append(root.val)
    Traversal(root.right, level+1, ds)
    Traversal(root.left, level+1, ds)


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

def lowestCommonAncestor(root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
    if root is None:
        return None
    
    return LCA(root,p,q)

def LCA(root, p, q):
    if root is None or root.val == p.val or root.val == q.val:
        return root
    
    left = LCA(root.left, p, q)
    right = LCA(root.right, p, q)

    if left is None:
        return right
    
    elif right is None:
        return left
    else:
        return 
        
def TreeEqualPartition(root):
    if root is None:
        return 0
    
    total = getSum(root)
    if total % 2 != 0:
        return 0
    # print(total // 2)
    res = [False]
    validateTree(root, total // 2, res)
    print(res)

def validateTree(root, target, res):

    if root is None:
        return 0
    
    leftTree = validateTree(root.left, target, res)
    rightTree = validateTree(root.right, target, res)
    
    total = root.val + leftTree + rightTree 
    if total == target:
        res[0] = True
    
    return total


def getSum(root):
    if root is None:
        return 0    
    return root.val + getSum(root.left) + getSum(root.right)


# root = TreeNode(5)
# n1 = TreeNode(3)
# n2 = TreeNode(7)
# n4 = TreeNode(4)
# n5 = TreeNode(6)
# n6 = TreeNode(5)
# n7 = TreeNode(6)


# root.left = n1
# root.right = n2
# n1.left = n4
# n1.right = n5
# n2.left = n6
# n2.right = n7
# TreeEqualPartition(root)

#                  5
#                /  \
#               3    7
#              / \  / \
#             4  6  5  6


def isLeaf(root):
    if root.left is None and root.right is None:
        return True
    return False


def sumBinaryTree(root):
    if root is None:
        return 1
    res = [ True ]
    isSumBinaryTree(root, res)
    print(res)


def isSumBinaryTree(root, res):
    if root is None:
        return 0

    if isLeaf(root):
        return root.val

    left = isSumBinaryTree(root.left, res)
    right = isSumBinaryTree(root.right, res)

    subTreeTotal = left + right
    print( (left, right ) )
    if root.val != subTreeTotal:
        res[0] = False
    
    return root.val + subTreeTotal


# root = TreeNode(26)
# n1 = TreeNode(10)
# n2 = TreeNode(3)
# n4 = TreeNode(4)
# n5 = TreeNode(6)
# n6 = TreeNode(3)

# root.left = n1
# root.right = n2
# n1.left = n4
# n1.right = n5
# n2.right = n6
# sumBinaryTree(root)

    # @param A : root node of tree
	# @param B : integer
	# @return an integer
def getPath(root, target):
    if root is None:
        return 0
    currentSum = root.val
    if currentSum == target:
        return 1
    
    res = [ ]
    path(root, res, target)
    print(res)


def path(root, res, target):
    if root is None:
        return False
    
    if root.val == target:
        res.append(root.val)
        return True
    
    left = path(root.left, res, target)
    right = path(root.right, res, target)


    if left or right == True:
        res.append(root.val)

    return left or right


# root = TreeNode(26)
# n1 = TreeNode(10)
# n2 = TreeNode(3)
# n4 = TreeNode(4)
# n5 = TreeNode(6)
# n6 = TreeNode(3)

# root.left = n1
# root.right = n2
# n1.left = n4
# n1.right = n5
# n2.right = n6

# getPath(root, 6)

# 0 1 knapsack problem

def knapsack(A,B,C):
    n = len(A)
    dp = [[float('inf') for _ in range(C + 1)] for _ in range(n + 1)]

    for i in range(C+1):
        dp[0][i] = 0

    for i in range(n+1):
        dp[i][0] = 0

    for i in range(1, n + 1):
        for j in range(1, C + 1):
            if j - B[i - 1] >= 0:
                # print('1 exe')
                dp[i][j] = max(dp[i - 1][j], A[i - 1] + dp[i - 1][j - B[i - 1]])
            else:
                # print('exe 2 ')
                dp[i][j] = dp[i - 1][j]

    # print(dp)
    print(dp[n][C])
    return dp[n][C]


def knapsackHelper(idx, weight, A, B, dp):
    if idx == 0 and weight == 0:
        return 0

    if idx < 0 or weight < 0:
        return 0
    
    if dp[idx][weight] != -1:
        return dp[idx][weight]
    
    # print( "pick is ", (idx-1, weight-B[idx]), "and dont pick is ", (idx-1, weight) )
    pick = 0
    if weight >= B[idx]:
        pick = A[idx] + knapsackHelper(idx-1, weight-B[idx], A, B,dp)
    dontPick = 0 + knapsackHelper(idx-1, weight, A, B,dp)

    dp[idx][weight] = max(pick, dontPick)
    return dp[idx][weight]

knapsack([12,20,15,6,10], [3,6,5,2,4], 8)



def unBoundedKnapsack(idx, weight, A, B, dp):
    if idx == 0 and weight == 0:
        return 0
    
    if idx < 0 or weight  < 0:
        return 0
    
    if dp[idx][weight] != -1:
        return dp[idx][weight]
    
    pick = float('-inf')
    if weight - B[idx] >=0:
        pick = A[idx] + unBoundedKnapsack(idx, weight-B[idx], A, B)
    
    dontPick = 0 + unBoundedKnapsack(idx-1, weight,A,B)

    dp[idx][weight] = max(pick, dontPick)
    return dp[idx][weight]

A = [1,1]
B= [2,1]
# ans = unBoundedKnapsack(1,3,A,B)
# print('a is ', ans)


def sendSignal(A):
    if A == 1:
        return 2
    
    off = 1
    on = 1
    res = float('inf')
    
    for i in range(2, A+1):
        curr_off = off + on
        curr_on = off
        if i == A:
            return curr_off + curr_on
        off = curr_off
        on = curr_on
        print((i, off, on))

    # print(res)
    return -1

# print(sendSignal(8))

def maximumUnits(boxTypes: List[List[int]], truckSize: int) -> int:
    if len(boxTypes) == 0:
        return 0
    
    sorted_list = sorted(boxTypes, key=lambda x : x[1], reverse=True)
    
    total_boxes = 0
    ans = 0
    print(sorted_list)

    for i in range(len(sorted_list)):
        if total_boxes + sorted_list[i][0] <= truckSize:
            ans += (sorted_list[i][0] * sorted_list[i][1])
            print('i is ', (i, sorted_list[i][0] * sorted_list[i][1] ))
            total_boxes += sorted_list[i][0]
        else:
            rem = truckSize - total_boxes
            ans += rem * sorted_list[i][1]
            break
    print(ans)
    return ans

maximumUnits([[1,3],[2,2],[3,1]], 4)








