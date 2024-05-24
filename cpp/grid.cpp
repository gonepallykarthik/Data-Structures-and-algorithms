#include <bits/stdc++.h>
using namespace std;


int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    if (grid[n - 1][m - 1] == 1) {
        return 0;
    }

    vector<vector<int>> dp(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 0) {
            if (i > 0 && dp[i - 1][0] == 0) {
                dp[i][0] = 0;
            }
            else {
                dp[i][0] = 1;
            }
        }
        else if (grid[i][0] == 1) {
            dp[i][0] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        if (grid[0][i] == 0) {
            if (i > 0 && dp[0][i - 1] == 0) {
                dp[0][i] = 0;
            }
            else {
                dp[0][i] = 1;
            }
        }
        else if (grid[0][i] == 1) {
            dp[0][i] = 0;
        }
    }

    for (auto row : dp) {
        for (auto num : row) {
            cout << num << "\t";
        }
        cout << endl;
    }

    for (int row = 1; row < n; row++) {
        for (int col = 1; col < m; col++) {
            if (grid[row][col] == 1) {
                dp[row][col] = 0;
            }
            else {
                dp[row][col] = dp[row][col - 1] + dp[row - 1][col];
            }
        }
    }

    return dp[n - 1][m - 1];
}

int minimumPathSuminTriangle(int row, int col, vector<vector<int>>& triangle) {
    if (row == 0) {
        return triangle[0][0];
    }

    if (row < 0 || col < 0 || col >= triangle[row].size()) {
        return INT_MAX;
    }

    int up = INT_MAX;
    int subProblem2 = minimumPathSuminTriangle(row - 1, col, triangle);
    if (subProblem2 != INT_MAX) {
        up = triangle[row][col] + subProblem2;
    }

    int left = INT_MAX;
    int subProblem = minimumPathSuminTriangle(row - 1, col - 1, triangle);
    if (subProblem != INT_MAX) {
        left = triangle[row][col] + subProblem;
    }
    // cout << "row and col is " << row << col << "\t" << up << left << endl;
    return min(up, left);
}


int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.size() == 0) {
        return 0;
    }
    int n = triangle.size();
    int ans = INT_MAX;
    for (int i = 0; i < triangle[n - 1].size(); i++) {
        ans = min(ans, minimumPathSuminTriangle(n - 1, i, triangle));
    }
    cout << ans;
    return ans;

}

int main() {
    vector<vector<int>> grid = {
        {0,1,0,0,0},
        { 1,0,0,0,0 },
        { 0,0,0,0,0 },
        { 0,0,0,0,0 }
    };
    // uniquePathsWithObstacles(grid);
    vector<vector<int>> triangle = {
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3}
    };
    // minimumTotal(triangle);
    // cout << INT_MAX + 1;
    return 0;

}