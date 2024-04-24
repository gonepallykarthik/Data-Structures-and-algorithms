#include <bits/stdc++.h>
using namespace std;

int fibonacci(int n, vector<int>& dp) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) return 1;

    if (dp[n] != -1) return dp[n];

    dp[n] = fibonacci(n - 1, dp) + fibonacci(n - 2, dp);
    return dp[n];
}

int stairs(int n, vector<int>& dp) {
    if (n == 0) return 1;
    if (n == 1) return 1;

    if (dp[n] != -1)return dp[n];

    dp[n] = stairs(n - 1, dp) + stairs(n - 2, dp);
    return dp[n];
}

int countMinSquaresHelper(int A, vector<int>& dp) {
    if (A == 0) return 0;
    if (A == 1) return 1;
    if (dp[A] != -1) return dp[A];

    int ans = INT_MAX;
    for (int j = 1; j * j <= A; j++) {
        ans = min(ans, countMinSquaresHelper(A - j * j, dp));
    }
    dp[A] = 1 + ans;
    return dp[A];
}

int minNumberOfCoinsForChange(int n, vector<int> denoms, vector<int>& dp) {
    // Write your code here.
    if (n == 0) return 0;
    if (dp[n] != -1) return dp[n];
    if (n < 0) return INT_MAX;

    int ans = INT_MAX;
    for (auto deno : denoms) {
        if (n >= deno) {
            ans = min(ans, minNumberOfCoinsForChange(n - deno, denoms, dp));
        }
    }
    if (ans == INT_MAX) {
        dp[n] = INT_MAX;
        return dp[n];
    }

    dp[n] = 1 + ans;
    return dp[n];
}

int maxSumwithoutAdjacent(vector<int> nums) {
    int n = nums.size();
    vector<int> dp(n, -1);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[n - 1];
}

int frogJump(int n, vector<int> heights) {
    if (n < 0) return INT_MAX;
    if (n == 0) return 0;

    int pick = INT_MAX;
    if (n > 1) {
        pick = abs(heights[n] - heights[n - 2]) + frogJump(n - 2, heights);
    }
    int dont_pick = abs(heights[n] - heights[n - 1]) + frogJump(n - 1, heights);

    return min(pick, dont_pick);
}

int minPathSum(vector<vector<int>> grid, int row, int col) {
    if (row == 0 && col == 0) {
        return grid[row][col];
    }

    // if (row < 0 || col < 0) return INT_MAX;

    int left = (col > 0) ? grid[row][col] + minPathSum(grid, row, col - 1) : INT_MAX;
    int up = (row > 0) ? grid[row][col] + minPathSum(grid, row - 1, col) : INT_MAX;

    return min(left, up);
}



int main() {
    // cout << "welcome";
    // int n = 6;
    // vector<int> dp(n + 1, -1);
    // int r = fibonacci(n, dp);
    // cout << r;
    // int n = 6;
    // vector<int> dp(n + 1, -1);
    // int r = countMinSquaresHelper(n, dp);
    // cout << r << endl;
    // int n = 7;
    // vector<int> denoms = { 2,4 };
    // vector<int> dp(n + 1, -1);
    // int r = minNumberOfCoinsForChange(n, denoms, dp);
    // cout << r;
    // vector<int>nums = { 2,3,4,5 };
    // int n = nums.size();
    // int res = maxSumwithoutAdjacent(nums);
    // cout << res << endl;
    // vector<int> nums = { 10,50,10 };
    // int n = nums.size();
    // int r = frogJump(n - 1, nums);
    // cout << r << endl;



    vector<vector<int> > A = {
        {1,2,3},
        {4,5,6},
    };
    int row = A.size();
    int col = A[0].size();

    int r = minPathSum(A, row - 1, col - 1);
    cout << r;
    // vector<int> maxs;
    // int n = A.size();
    // int col = 0;
    // int m = A[0].size();
    // while (col < m) {
    //     int max_num = INT_MIN;
    //     for (int row = 0; row < n; row++) {
    //         max_num = max(max_num, A[row][col]);
    //     }
    //     maxs.push_back(max_num);
    //     col += 1;
    // }


    // for (auto num : maxs)
    // {
    //     cout << num << "\t";
    // }
    return 0;
}