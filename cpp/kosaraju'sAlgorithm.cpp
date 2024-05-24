#include <bits/stdc++.h>
using namespace std;

void dfsRec(int node, vector<vector<int>>& adj, stack<int>& st, vector<bool>& visited) {
    visited[node] = true;
    for (auto neighbor : adj[node]) {
        if (visited[neighbor] == false) {
            dfsRec(neighbor, adj, st, visited);
        }
    }

    st.push(node);

}

void dfs_Traversal(int node, vector<vector<int>>& graph, vector<int>& visited) {
    visited[node] = 1;
    for (auto neighbor : graph[node]) {
        if (visited[neighbor] == -1) {
            dfs_Traversal(neighbor, graph, visited);
        }
    }
}

int kosaraju(int V, vector<vector<int>>& adj)
{
    //code here
    stack<int> st;
    vector<bool> dfsVisited(V, false);
    for (int i = 0; i < V; i++) {
        if (dfsVisited[i] == false) {
            dfsRec(i, adj, st, dfsVisited);
        }
    }

    vector<int> order;
    while (!st.empty()) {
        order.push_back(st.top());
        st.pop();
    }

    vector<vector<int>> transpose(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            transpose[adj[i][j]].push_back(i);
        }
    }
    int ans = 0;
    vector<int> visited(order.size(), -1);
    for (int i = 0; i < order.size(); i++) {
        if (visited[order[i]] == -1) {
            ans += 1;
            dfs_Traversal(order[i], transpose, visited);
        }
    }


    // for (auto edges : transpose) {
    //     for (auto num : edges) {
    //         cout << num << "\t";
    //     }
    //     cout << endl;
    // }
    return ans;
}

vector<int> maximumDepth(int A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& E, vector<int>& F) {
    queue<pair<int, int>> q;
    vector<vector<int>> graph(A + 1);
    for (int i = 0; i < B.size(); i++) {
        int src = B[i];
        int des = C[i];
        graph[src].push_back(des);
        graph[des].push_back(src);
    }
    int max_depth = 0;
    vector<int> visited(A + 1, -1);
    map<int, vector<int>> mp;

    q.push(make_pair(0, 1));
    while (!q.empty()) {
        int depth = q.front().first;
        int node = q.front().second;
        max_depth = max(max_depth, depth);
        q.pop();
        if (visited[node] == 1) {
            continue;
        }
        visited[node] = 1;
        mp[depth].push_back(D[node - 1]);

        for (auto neighbor : graph[node]) {
            if (visited[neighbor] == -1) {
                q.push(make_pair(depth + 1, neighbor));
            }
        }
    }

    for (auto& pair : mp) {
        sort(pair.second.begin(), pair.second.end());
    }

    // for (auto pair : mp) {
    //     for (auto num : pair.second) {
    //         cout << num << "\t";
    //     }
    //     cout << endl;
    // }

    // process queries 
    vector<int> res(E.size());
    for (int i = 0; i < E.size(); i++) {
        int L = E[i];
        int x = F[i];
        int level = L % (max_depth + 1);

        // apply binary search on that level 
        vector<int> nums = mp[level];
        int left = 0;
        int right = nums.size() - 1;
        int ans = INT_MAX;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= x) {
                ans = min(ans, nums[mid]);
            }

            if (nums[mid] < x) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        res[i] = (ans);
    }
    return res;
}

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    if (grid[0][0] == 1) {
        return -1;
    }
    vector<vector<int>> visited(n, vector<int>(m, -1));
    queue< pair<int, pair<int, int>>> q;
    q.push({ 1, {0,0} });
    int ans = INT_MAX;

    while (!q.empty()) {
        int distance = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();

        if (visited[row][col] == 1) {
            continue;
        }
        visited[row][col] = 1;

        if (row == n - 1 && col == m - 1) {
            ans = min(ans, distance);
        }

        vector<vector<int>> directions = { {-1,0}, {1,0}, {0,1}, {0,-1}, {-1,-1}, {-1,1}, {1,1}, {1,-1} };
        for (int i = 0; i < directions.size(); i++) {
            int new_row = row + directions[i][0];
            int new_col = col + directions[i][1];
            if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < m && grid[new_row][new_col] == 0 && visited[new_row][new_col] == -1) {
                q.push({ distance + 1, {new_row, new_col} });
            }
        }
    }

    return ans;
}

int BFS_Traversal(vector<vector<int>> grid, int row, int col) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, -1));
    int ans = INT_MAX;
    queue< pair<int, pair<int, int>> > q;
    q.push({ 0, {row,col} });
    while (!q.empty()) {
        int distance = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();

        if (grid[row][col] == 1) {
            ans = min(ans, distance);
        }
        if (visited[row][col] == 1) {
            continue;
        }

        visited[row][col] = 1;

        vector<vector<int>> directions = { {-1,0}, {1,0}, {0,1}, {0,-1} };
        for (int i = 0; i < directions.size(); i++) {
            int new_row = row + directions[i][0];
            int new_col = col + directions[i][1];
            if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < m && visited[new_row][new_col] == -1) {
                q.push({ distance + 1, {new_row, new_col} });
            }
        }
    }

    return ans;
}

//Function to find distance of nearest 1 in the grid for each cell.
vector<vector<int>>nearest(vector<vector<int>>grid)
{
    // Code here
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> res(n, vector<int>(m, -1));
    vector<vector<int>> visited(n, vector<int>(m, -1));
    queue<pair<int, pair<int, int>>> q;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (grid[row][col] == 1) {
                res[row][col] = 0;
                q.push({ 0, {row,col} });
                visited[row][col] = 1;
            }
        }
    }

    while (!q.empty()) {
        int distance = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();

        if (visited[row][col] == 1) {
            continue;
        }

        visited[row][col] = 1;

        if (grid[row][col] == 0) {
            res[row][col] = distance;
        }

        vector<vector<int>> directions = { {-1,0}, {1,0}, {0,1}, {0,-1} };
        for (int i = 0; i < directions.size(); i++) {
            int new_row = row + directions[i][0];
            int new_col = col + directions[i][1];
            if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < m && visited[new_row][new_col] == -1) {
                q.push({ distance + 1, {new_row, new_col} });
            }
        }
    }

    return res;
}

int numberOfEnclaves(vector<vector<int>>& grid) {
    // Code here
    int n = grid.size();
    int m = grid[0].size();
    queue< pair<int, int>> q;
    vector<vector<int>> visited(n, vector<int>(m, -1));
    for (int col = 0; col < m; col++) {
        if (grid[0][col] == 1) {
            q.push(make_pair(0, col));
        }
        if (grid[n - 1][col] == 1) {
            q.push(make_pair(n - 1, col));
        }
    }

    for (int row = 0; row < n; row++) {
        if (grid[row][0] == 1) {
            q.push(make_pair(row, 0));
        }

        if (grid[row][m - 1] == 1) {
            q.push(make_pair(row, m - 1));
        }
    }

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if (visited[row][col] == 1) {
            continue;
        }

        visited[row][col] = 1;
        grid[row][col] = 2;
        vector<int> dr = { -1, 0, 1, 0 };
        vector<int> dc = { 0, -1, 0, 1 };
        for (int i = 0; i < 4; i++) {
            int new_row = row + dr[i];
            int new_col = col + dc[i];
            if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < m && visited[new_row][new_col] == -1 && grid[new_row][new_col] == 1) {
                q.push(make_pair(new_row, new_col));
            }
        }
    }

    int cnt = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (grid[row][col] == 1) cnt += 1;
        }

    }

    return cnt;
}
bool DFS(int node, int parent, vector<int> adj[], vector<int>& visited) {
    visited[node] = 1;

    for (auto neighbor : adj[node]) {
        if (visited[neighbor] == -1) {
            if (DFS(neighbor, node, adj, visited)) {
                return true;
            }
        }

        else if (visited[neighbor] == 1 && neighbor != parent) {
            return true;
        }
    }
    return false;
}

func()

bool isCycle(int V, vector<int> adj[]) {
    // Code here
    vector<int> visited(V, -1);
    for (int i = 0; i < V; i++) {
        if (visited[i] == -1) {
            bool res = DFS(i, -1, adj, visited);
            cout << "dfs res is  " + res << endl;
        }
    }

    return false;
}


int main() {
    // cout << "welcome to this application";
    // vector<vector<int>> edges = {
    //     {1},
    //     {2,3},
    //     {0},
    //     {4},
    //     {}
    // };
    // int V = 5;
    // int ans = kosaraju(V, edges);
    // cout << ans;


    // int A = 5;
    // vector<int> B = { 1, 4, 3, 1 };
    // vector<int> C = { 5, 2, 4, 4 };
    // vector<int> D = { 7, 38, 27, 37, 1 };
    // vector<int> E = { 1, 1, 2 };
    // vector<int> F = { 32, 18, 26 };
    // vector<int> res = maximumDepth(A, B, C, D, E, F);
    // for (auto num : res) {
    //     cout << num << "\t";
    // }

    vector<vector<int>> grid = {
            {0, 0, 0, 1},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 1},
            {0, 1, 1, 0} };

    // int ans = shortestPathBinaryMatrix(grid);
    // cout << ans;
    // numberOfEnclaves(grid);
    int V = 5;
    vector<int> adj[] = { {}, {2}, {1, 3}, {2} };
    bool res = isCycle(V, adj);
    cout << res;
    return 0;
}