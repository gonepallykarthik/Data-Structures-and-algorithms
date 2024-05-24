#include <bits/stdc++.h>
using namespace std;

bool DFS(int node, vector<int> adj[], vector<int>& visited, vector<int>& path) {
    visited[node] = 1;
    path[node] = 1;
    for (auto neigbhor : adj[node]) {
        if (path[neigbhor] == 1) return true;
    }

    for (auto neighbor : adj[node]) {
        if (visited[neighbor] == -1) {
            if (DFS(neighbor, adj, visited, path)) return true;
        }
    }

    path[node] = -1;
    return false;
}



// Function to detect cycle in a directed graph.
bool isCyclic(int V, vector<int> adj[]) {
    // code here
    vector<int> visited(V, -1);
    vector<int> path(V, -1);
    for (int i = 0; i < V; i++) {
        if (DFS(i, adj, visited, path)) {
            return true;
        }
    }
    for (auto num : path) {
        cout << num << "\t";
    }
    return false;
}

int lengthOfLIS(vector<int>& nums) {
    if (nums.size() == 0) {
        return -1;
    }
    vector<int> dp(nums.size(), 0);
    dp[0] = 1;
    for (int i = 1; i < nums.size(); i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
    }
    int maxi = INT_MIN;
    for (int i = 0; i < dp.size(); i++) {
        maxi = max(maxi, dp[i]);
    }

    return maxi;
}

int coinChangeHelper(int amount, vector<int>& coins, vector<int>& dp) {
    if (amount == 0) {
        return 0;
    }

    if (dp[amount] != -1) {
        return dp[amount];
    }

    int ans = INT_MAX;
    for (int i = 0; i < coins.size(); i++) {
        if (amount - coins[i] >= 0) {
            int subProblem = (ans, 1 + coinChangeHelper(amount - coins[i], coins, dp));
            if (subProblem != INT_MAX) {
                ans = min(ans, 1 + subProblem);
            }
        }
    }
    dp[amount] = ans;
    return dp[amount];
}

int minCoinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, -1);
    return coinChangeHelper(amount, coins, dp);
}

int minDistanceHelper(int idx1, int idx2, string word1, string word2) {
    if (idx1 < 0) {
        return idx2 + 1;
    }
    if (idx2 < 0) {
        return idx1 + 1;
    }

    if (word1[idx1] == word2[idx2]) {
        return minDistanceHelper(idx1 - 1, idx2 - 1, word1, word2);
    }

    int insertion = minDistanceHelper(idx1 - 1, idx2, word1, word2);
    int deletion = minDistanceHelper(idx1, idx2 - 1, word1, word2);
    int replace = minDistanceHelper(idx1 - 1, idx2 - 1, word1, word2);
    return 1 + min(insertion, min(deletion, replace));
}


int minDistance(string word1, string word2) {
    int l1 = word1.size();
    int l2 = word2.size();
    return minDistanceHelper(l1 - 1, l2 - 1, word1, word2);
}

int frogJump(int idx, vector<int> nums) {
    if (idx <= 0) {
        return 0;
    }

    int firstStep = abs(nums[idx] - nums[idx - 1]) + frogJump(idx - 1, nums);
    int secondStep = INT_MAX;
    if (idx - 2 >= 0) {
        secondStep = abs(nums[idx] - nums[idx - 2]) + frogJump(idx - 2, nums);
    }
    return min(firstStep, secondStep);
}

int HouseRobber(vector<int> nums) {
    int n = nums.size();
    vector<int> dp(n, -1);
    dp[0] = nums[0];
    for (int i = 1; i < n; i++) {
        if (i - 2 >= 0) {
            dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
        }
        else {
            dp[i] = dp[i - 1];
        }
    }
    return dp[n - 1];
}

int SubsetSum(int idx, vector<int> nums, int currentSum, int target, vector<vector<int>>& dp) {
    if (currentSum == target) {
        return 1;
    }

    if (idx >= nums.size() || currentSum > target) {
        return 0;
    }

    if (dp[idx][currentSum] != -1) {
        return dp[idx][currentSum];
    }
    // pick the element
    int include = 0;
    if (currentSum + nums[idx] <= target) {
        include = SubsetSum(idx + 1, nums, currentSum + nums[idx], target, dp);
    }

    // dont pick the element
    int dontInclude = SubsetSum(idx + 1, nums, currentSum, target, dp);

    dp[idx][currentSum] = include || dontInclude;
    return dp[idx][currentSum];
}

int minimumDifference(vector<int>& nums) {
    int totalSum = 0;
    for (auto num : nums) {
        totalSum += num;
    }
    int n = nums.size();
    vector<vector<bool>> dp(n, vector<bool>(totalSum + 1, false));
    for (int i = 0; i < n; i++) {
        dp[i][0] = true;
    }

    if (nums[0] <= totalSum) {
        dp[0][nums[0]] = true;
    }

    for (int i = 1; i < n; i++) {
        for (int target = 1; target <= totalSum; target++) {
            bool dontPick = dp[i - 1][target];
            bool pick = false;
            if (nums[i] <= target) {
                pick = dp[i - 1][target - nums[i]];
            }
            dp[i][target] = dontPick | pick;
        }
    }

    int min_diff = INT_MAX;
    for (int i = 0; i <= totalSum; i++) {
        if (dp[n - 1][i] == true) {
            int partition1 = i;
            int partition2 = totalSum - i;
            min_diff = min(min_diff, abs(partition1 - partition2));
        }
    }

    return min_diff;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int lastIdx = (m + n) - 1;
    m = m - 1;
    n = n - 1;

    while (m >= 0 && n >= 0) {
        if (nums1[m] <= nums2[n]) {
            nums1[lastIdx] = nums2[n];
            n -= 1;
        }
        else if (nums1[m] > nums2[n]) {
            nums1[lastIdx] = nums1[m];
            m -= 1;
        }
        lastIdx -= 1;
    }

    while (n >= 0) {
        nums1[lastIdx] = nums2[n - 1];
        n -= 1;
        lastIdx -= 1;
    }
}

int LIS(int idx, vector<int>& nums, int prevIdx, vector<vector<int>>& dp) {
    if (idx == nums.size()) {
        return 0;
    }

    if (dp[idx][prevIdx + 1] != -1) {
        return dp[idx][prevIdx + 1];
    }

    int take = 0;
    if (prevIdx == -1 || nums[prevIdx] < nums[idx]) {
        take = 1 + LIS(idx + 1, nums, idx, dp);
    }
    int noTake = 0 + LIS(idx + 1, nums, prevIdx, dp);

    return dp[idx][prevIdx + 1] = max(take, noTake);
}

bool pathExist(int row, int col, vector<vector<int>>& grid, int n, int m, int& cherrys) {
    if (grid[row][col] == 1) {
        cherrys += 1;
        grid[row][col] = 0;
    }

    if (row == n - 1 && col == m - 1) {
        return true;
    }

    if (row >= n || col >= m || grid[row][col] == -1) {
        return false;
    }

    bool right = pathExist(row, col + 1, grid, n, m, cherrys);
    bool down = pathExist(row + 1, col, grid, n, m, cherrys);

    return right || down;
}

void bottomToUp(int row, int col, vector<vector<int>>& grid, int& cherrys) {
    if (row == 0 && col == 0) {
        return;
    }

    if (grid[row][col] == 1) {
        cherrys += 1;
        grid[row][col] = 0;
    }

    if (col - 1 >= 0 && grid[row][col - 1] != -1) {
        bottomToUp(row, col - 1, grid, cherrys);
    }
    if (row - 1 >= 0 && grid[row - 1][col] != -1) {
        bottomToUp(row - 1, col, grid, cherrys);
    }

}


int cherryPickup(vector<vector<int>>& grid) {
    int cherrys = 0;
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, -1));
    // cout << "ans is  " << pathExist(0, 0, grid, n, m, cherrys) << endl;
    if (pathExist(0, 0, grid, n, m, cherrys) == false) {
        return 0;
    }
    bottomToUp(n - 1, m - 1, grid, cherrys);

    return cherrys;
}

int main() {
    // cout << "welcome to this application";
    // int V = 3;
    // vector<int> adj[] = { {1}, {2}, {} };
    // isCyclic(V, adj);
    // vector<int>nums = { 10, 9, 2, 5, 3, 7, 101, 18 };
    // int r = lengthOfLIS(nums);
    // cout << r;
    // vector<int> coins = { 1,2,5 };
    // int amount = 7;
    // int r = minCoinChange(coins, amount);
    // cout << r;
    // int res = minDistance("horse", "ros");
    // cout << res;
    // vector<int> nums = { 2,-1,0,4,-2,-9 };
    // int r = frogJump(nums.size() - 1, nums);
    // cout << r;
    // int res = HouseRobber(nums);
    // cout << res;
    // cout << minimumDifference(nums);
    // vector<int> nums1 = { 1,2,3,0,0,0 };
    // vector<int> nums2 = { 2,5,6 };
    // merge(nums1, 6, nums2, 3);
    // vector<int> nums = { 10,9,2,5,3,7,101,18 };
    // cout << LIS(0, nums, -1);
    vector<vector<int>> grid = {
        {1}
    };
    cout << cherryPickup(grid);
    return 0;
}