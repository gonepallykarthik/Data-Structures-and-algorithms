#include<bits/stdc++.h>
using namespace std;

int tribonacci(int n) {
    int first = 0;
    int second = 1;
    int third = 1;
    for (int i = 3; i <= n; i++) {
        int curr = first + second + third;
        first = second;
        second = third;
        third = curr;
    }

    return third;
}

bool divisorHelper(int n, int cnt) {
    if (n == 1) {
        if (cnt % 2 == 0) return false;
        else return true;
    }

    bool ans = true;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            ans = ans & divisorHelper(n - i, cnt + 1);
        }
    }
    return ans;
}

bool divisorGame(int n) {
    return divisorHelper(n, 0);
}
int stoneGameHelper(int left, int right, vector<vector<int>>& dp, vector<int>& piles) {
    if (left > right) {
        return 0;
    }
    if (dp[left][right] != -1) {
        return dp[left][right];
    }

    bool even = (right - left) % 2 ? true : false;
    int left_val = even == true ? piles[left] : 0;
    int right_val = even == true ? piles[right] : 0;

    dp[left][right] = max(left_val + stoneGameHelper(left + 1, right, dp, piles), right_val + stoneGameHelper(left, right - 1, dp, piles));

    return dp[left][right];
}

void dfs(int src, vector<vector<int>>& graph, vector<int>& visited) {
    visited[src] = 1;

    for (auto neighbor : graph[src]) {
        cout << "neighbors are of" << src << "are " << neighbor << endl;
        if (visited[neighbor] == -1) {
            dfs(neighbor, graph, visited);
        }
    }
}

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    int m = isConnected[0].size();
    vector<vector<int>> graph(n);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (isConnected[row][col] == 1) {
                graph[row].push_back(col);
            }
        }
    }
    vector<int> visited(n, -1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] == -1) {
            ans += 1;
            dfs(i, graph, visited);
        }
    }
    return ans;
    // for (auto x : graph) {
    //     for (auto num : x) {
    //         cout << num << "\t";
    //     }
    //     cout << endl;
    // }
}

void Traversal(int row, int col, vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    grid[row][col] = 2;
    vector<int> dr = { -1, 0, 1, 0 };
    vector<int> dc = { 0, -1, 0, 1 };

    for (int i = 0; i < 4; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < m && grid[new_row][new_col] == 1) {
            Traversal(new_row, new_col, grid);
        }
    }
}

int numEnclaves(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    for (int col = 0; col < m; col++) {
        if (grid[0][col] == 1) {
            Traversal(0, col, grid);
        }
    }


    for (int row = 0; row < n; row++) {
        if (grid[row][0] == 1) {
            Traversal(row, 0, grid);
        }
    }

    for (int col = 0; col < m; col++) {
        if (grid[n - 1][col] == 1) {
            Traversal(n - 1, col, grid);
        }
    }

    for (int row = 0; row < n; row++) {
        if (grid[row][m - 1] == 1) {
            Traversal(row, m - 1, grid);
        }
    }
    int ans = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (grid[row][col] == 1) {
                ans += 1;
            }
        }
    }
    return ans;
}


bool stoneGame(vector<int> piles) {
    int n = piles.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    int sum = 0;
    for (auto num : piles) {
        sum += num;
    }
    int r = stoneGameHelper(0, piles.size() - 1, dp, piles);
    cout << r;
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    set<int> keys_taken;
    int n = rooms.size();
    for (auto num : rooms[0]) {
        keys_taken.insert(num);
    }

    for (int i = 1; i < n; i++) {
        if (keys_taken.find(i) == keys_taken.end()) {
            return false;
        }
        for (auto num : rooms[i]) {
            keys_taken.insert(num);
        }
    }

    return true;
}

int knight(int A, int B, int C, int D, int E, int F) {
    //(C,D) -> source
    // (E,F) -> des
    // A*B chess board dimensions
    queue< pair<int, pair<int, int>> > q;
    vector<vector<int>> visited(A, vector<int>(B, -1));
    C = C - 1;
    D = D - 1;
    E = E - 1;
    F = F - 1;
    q.push({ 0, {C,D} });

    while (!q.empty()) {
        int steps = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();
        if (visited[row][col] == 1) {
            continue;
        }
        visited[row][col] = 1;
        if (row == E && col == F) {
            return steps;
        }

        // visited all 8 directions
        vector<vector<int>> directions = { {-1,2}, {1,2}, {1,-2}, {-1,-2}, {2,1}, {-2,1}, {-2,-1}, {2,-1} };
        for (int i = 0; i < 8; i++) {
            int new_row = row + directions[i][0];
            int new_col = col + directions[i][1];
            if (new_row >= 0 && new_row < A && new_col >= 0 && new_col < B && visited[new_row][new_col] == -1) {
                q.push({ steps + 1, {new_row, new_col} });
            }
        }
    }

    return -1;
}

int maxProfit(vector<int>& prices) {
    if (prices.size() == 0) {
        return -1;
    }

    vector<vector<int>> dp(3, vector<int>(prices.size(), 0));
    for (int i = 1; i < 3; i++) {
        int max_profit = INT_MIN;
        for (int j = 1; j < i; j++) {
            max_profit = max(max_profit, dp[i - 1][j - 1] - prices[j - 1]);
            dp[i][j] = max(dp[i - 1][j], prices[j] + max_profit);
        }
    }
    return dp[2][prices.size() - 1];
}

int main() {
    // cout << "welcome";
    // int r = tribonacci(5);
    // cout << r << endl;
    // bool r1 = divisorGame(4);
    //   cout << r1;
    // stoneGame(vector<int>{5, 3, 4, 5});
    // vector<vector<int>> graph = {
    //     {0,1,1,0},
    //     {0,0,1,0},
    //     {0,0,1,0},
    //     {0,0,0,0}
    // };

    // int ans = findCircleNum(graph);
    // cout << ans;
    // numEnclaves(graph);
    // vector<vector<int>> keys = {
    //     {1,3},
    //     {3,0,1},
    //     {2},
    //     {0}
    // };
    // bool canOpen = canVisitAllRooms(keys);
    // cout << canOpen;

    int ans = knight(8, 8, 1, 1, 8, 8);
    cout << ans;
    return 0;
}