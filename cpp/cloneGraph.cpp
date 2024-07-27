#include <bits/stdc++.h>
using namespace std;

// string reverseParentheses(string s) {
//     if (s.size() == 0) {
//         return "";
//     }

//     stack<char> st;
//     for (auto character : s) {
//         char curr_char = character;

//         // if it is not closing parenthesis
//         if (curr_char != ')') {
//             st.push(curr_char);
//         }

//         // other characters push to stack
//         else {
//             string r = "";
//             while (st.top() != '(')
//             {
//                 r += st.top();
//                 st.pop();
//             }

//             // remove opening parenthesis
//             st.pop();
//             cout << "r is " << r << endl;
//             for (auto character : r) {
//                 st.push(character);
//             }
//         }
//     }
//     string res = "";
//     while (!st.empty()) {
//         res = st.top() + res;
//         st.pop();
//     }
//     return res;
// }

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
 // UndirectedGraphNode* Solution::cloneGraph(UndirectedGraphNode* node) {

 // }

int helper(int i, int j, vector<int>& nums, vector<vector<int>>& dp) {
    if (i > j) {
        return 0;
    }
    if (i == j) {
        return nums[i];
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int take_i = nums[i] + min(helper(i + 2, j, nums, dp), helper(i + 1, j - 1, nums, dp));
    int take_j = nums[j] + min(helper(i + 1, j - 1, nums, dp), helper(i, j - 2, nums, dp));
    dp[i][j] = max(take_i, take_j);
    return dp[i][j];
}


bool predictTheWinner(vector<int>& nums) {
    if (nums.size() == 1) {
        return true;
    }
    int total_score = 0;
    for (auto num : nums) {
        total_score += num;
    }
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    int p1_score = helper(0, nums.size() - 1, nums, dp);
    int p2_score = total_score - p1_score;

    return p1_score >= p2_score;
}

int minPathSum(int i, int j, vector<vector<int>>& matrix, int n, int m, vector<vector<int>>& dp) {
    if (j < 0 || j >= m) {
        return 1e9;
    }

    if (i == 0) {
        return matrix[i][j];
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int s1 = matrix[i][j] + minPathSum(i - 1, j, matrix, n, m, dp);

    int s2 = matrix[i][j] + minPathSum(i - 1, j - 1, matrix, n, m, dp);

    int s3 = matrix[i][j] + minPathSum(i - 1, j + 1, matrix, n, m, dp);

    return dp[i][j] = min(s1, min(s2, s3));
}

// int func() {
//     vector<vector<int>> dp(n, vector<int>(m, -1));

//     for (int i = 0; i < m; i++) {
//         dp[0][i] = matrix[0][i];
//     }

//     for (int i = 1; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             int s1 = matrix[i][j] + dp[i - 1][j];
//             int s2 = 1e9;
//             if (j - 1 >= 0) {
//                 s2 = matrix[i][j] + dp[i - 1][j - 1];
//             }
//             int s3 = 1e9;
//             if (j + 1 < m) {
//                 s3 = matrix[i][j] + dp[i - 1][j + 1];
//             }
//             dp[i][j] = min(s1, min(s2, s3));
//         }
//     }

//     return dp[n - 1][m - 1];

// }

int minFallingPathSumHelper(int row, int col, vector<vector<int>>& grid, vector<vector<int>>& dp, int n, int m) {
    // base case
    if (row == 0) {
        return grid[row][col];
    }

    if (dp[row][col] != -1) return dp[row][col];

    int ans = 1e9;
    for (int c = 0; c < m; c++) {
        if (c != col) {
            ans = min(ans, grid[row][col] + minFallingPathSumHelper(row - 1, c, grid, dp, n, m));
        }
    }

    return dp[row][col] = ans;
}

int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));

    int ans = 1e9;
    for (int j = 0; j < m; j++) {
        cout << minFallingPathSumHelper(n - 1, j, grid, dp, n, m) << endl;
    }

    return ans;
}

vector<int> distinctElementsInWindow(vector<int> nums, int k) {
    vector<int> res;
    map<int, int> mp;
    int distinct = 0;
    for (int i = 0; i < k; i++) {
        if (mp.find(nums[i]) == mp.end()) {
            distinct += 1;
        }
        mp[nums[i]] += 1;
    }

    res.push_back(distinct);

    int start = 0;
    int end = k;

    while (end < nums.size()) {
        mp[nums[start]] -= 1;
        if (mp[nums[start]] == 0) {
            distinct -= 1;
            mp.erase(nums[start]);
        }

        if (mp.find(nums[end]) == mp.end()) {
            distinct += 1;
        }

        res.push_back(distinct);
        mp[nums[end]] += 1;
        start += 1;
        end += 1;
    }

    return res;
}


int main() {
    // cout << "welcome";
    // string str = "(u(love)i)";
    // cout << reverseParentheses(str);
    // vector<int> nums = { 1,5,233,7 };
    // predictTheWinner(nums);
    vector<vector<int>>
        grid = { {1, 2, 3 }, {4, 5, 6 }, {7, 8, 9} };
    // minFallingPathSum(grid);

    vector<int> res = distinctElementsInWindow(vector<int>{1, 2, 2, 3, 4, 4, 5}, 3);
    for (auto num : res) {
        cout << num << "\t";
    }
    return 0;
}