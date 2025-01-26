#include <bits/stdc++.h>
using namespace std;

bool dfsTraversal(int currNode, vector<vector<int>>& graph, vector<int>& visited, int targetNode) {
    visited[currNode] = 1;
    // cout << currNode << "\t";
    for (auto neighbors : graph[currNode]) {
        // cout << "neighbor is" << neighbors << endl;
        if (visited[neighbors] != 1) {
            if (neighbors == targetNode) {
                return true;
            }
            else {
                if (dfsTraversal(neighbors, graph, visited, targetNode)) {
                    return true;
                }

            }
        }
    }
    return false;
}

bool detectCycle(int currNode, vector<vector<int>>& graph, vector<int>& visited, vector<int>& path) {
    visited[currNode] = 1;
    path[currNode] = 1;
    for (auto neighbors : graph[currNode]) {
        if (path[neighbors] == 1) {
            return true;
        }
        else if (visited[neighbors] != 1) {
            if (detectCycle(neighbors, graph, visited, path)) {
                return true;
            }
        }
    }

    path[currNode] = 0;
    return false;
}

vector<int> smallestRange(vector<vector<int>>& nums) {
    if (nums.size() == 0) {
        return {};
    }

    vector<int> ans(2);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater< pair<int, pair<int, int>>> >pq;
    int min;
    int maxi = INT_MIN;
    for (int i = 0; i < nums.size(); i++) {
        pq.push(make_pair(nums[i][0], make_pair(i, 0)));
        maxi = max(maxi, nums[i][0]);
    }
    min = pq.top().first;
    ans[0] = min;
    ans[1] = maxi;

    while (pq.size() == nums.size())
    {
        pair<int, pair<int, int>> topEle = pq.top();
        int ele = topEle.first;
        int row = topEle.second.first;
        int col = topEle.second.second;
        pq.pop();

        if (col + 1 < nums[row].size()) {
            pq.push(make_pair(nums[row][col + 1], make_pair(row, col + 1)));
            maxi = max(maxi, nums[row][col + 1]);
            min = pq.top().first;
            if (maxi - min < ans[1] - ans[0]) {
                ans[0] = min;
                ans[1] = maxi;
            }

        }
    }
    return ans;
}

bool isPossible(vector<int>& target) {


    int sum = 0;
    priority_queue<int> pq;
    for (int i = 0; i < target.size(); i++) {
        pq.push(target[i]);
        sum += target[i];
    }

    int maxElement, remSum, Element;

    while (pq.top() != -1) {
        maxElement = pq.top();
        pq.pop();
        remSum = sum - maxElement;
        if (remSum <= 0 || remSum >= maxElement) {
            return 0;
        }

        Element = maxElement - remSum;
        sum = remSum + Element;
        pq.push(Element);
    }
    return 1;
}

vector<vector<int>> get_all_neighbors(int row, int col, vector<vector<int>>& matrix, vector<vector<int>>& visited) {
    vector<vector<int>> neighbors;
    int m = matrix.size();
    int n = matrix[0].size();
    if (row - 1 >= 0 && visited[row - 1][col] == 0) {
        neighbors.push_back({ row - 1, col });
    }

    if (col - 1 >= 0 && visited[row][col - 1] == 0) {
        neighbors.push_back({ row, col - 1 });
    }

    if (row + 1 < m && visited[row + 1][col] == 0) {
        neighbors.push_back({ row + 1, col });
    }

    if (col + 1 < n && visited[row][col + 1] == 0) {
        neighbors.push_back({ row, col + 1 });
    }

    // top left diagnol
    if (row - 1 >= 0 && col - 1 >= 0 && visited[row - 1][col - 1] == 0) {
        neighbors.push_back({ row - 1, col - 1 });
    }

    //top right diagnol
    if (row - 1 >= 0 && col + 1 < n && visited[row - 1][col + 1] == 0) {
        neighbors.push_back({ row - 1, col + 1 });
    }

    // bottom left diagnol
    if (row + 1 < m && col - 1 >= 0 && visited[row + 1][col - 1] == 0) {
        neighbors.push_back({ row + 1, col - 1 });
    }

    // bottom right diagnol
    if (row + 1 < m && col + 1 < n && visited[row + 1][col + 1] == 0) {
        neighbors.push_back({ row + 1, col + 1 });
    }

    return neighbors;
}

void Traversal(int row, int col, vector<vector<int>>& matrix, vector<vector<int>>& visited) {
    visited[row][col] = 1;

    vector<vector<int>>neighbors = get_all_neighbors(row, col, matrix, visited);
    for (auto neighbor : neighbors) {
        int nrow = neighbor[0];
        int ncol = neighbor[1];
        if (visited[nrow][ncol] == 0 && matrix[nrow][ncol] == 1) {
            Traversal(nrow, ncol, matrix, visited);
        }
    }

}


void dfs(int row, int col, vector<vector<char>>& A) {
    A[row][col] = '1';

    int m = A.size();
    int n = A[0].size();

    if (col - 1 >= 0 && A[row][col - 1] == 'O') {
        dfs(row, col - 1, A);
    }

    if (col + 1 < n && A[row][col + 1] == 'O') {
        dfs(row, col + 1, A);
    }

    if (row - 1 >= 0 && A[row - 1][col] == 'O') {
        dfs(row - 1, col, A);
    }

    if (row + 1 < m && A[row + 1][col] == 'O') {
        dfs(row + 1, col, A);
    }
}

void solve(vector<vector<char> >& A) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
    if (A.size() == 0) { return; }
    int m = A.size();
    int n = A[0].size();

    int row = 0;
    for (int col = 0; col < n; col++) {
        if (A[row][col] == 'O') {
            // call dfs function
            dfs(row, col, A);
        }
    }

    int col = n - 1;
    for (int r = 0; r < m; r++) {
        if (A[r][col] == 'O') {
            dfs(r, col, A);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (A[m - 1][i] == 'O') {
            dfs(m - 1, i, A);
        }
    }

    for (int r = 0; r < m; r++) {
        if (A[r][0] == 'O') {
            dfs(r, 0, A);
        }
    }

    for (int row = 0; row < m; row++) {
        for (int col = 0; col < n; col++) {
            if (A[row][col] == 'O') {
                A[row][col] = 'X';
            }
        }
    }

    for (int row = 0; row < m; row++) {
        for (int col = 0; col < n; col++) {
            if (A[row][col] == '1') {
                A[row][col] = 'O';
            }
        }
    }

    for (int i = 0; i < A.size(); i++) {
        for (int col = 0; col < A[0].size(); col++) {
            cout << A[i][col] << "\t";
        }
        cout << endl;
    }

}

class Node {
public:
    int row;
    int col;
    int time;
    Node(int r, int c, int t) {
        row = r;
        col = c;
        time = t;
    }
};

bool isValid(int row, int col, vector<vector<int>>& visited, vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();

    if (row >= 0 && row < n && col >= 0 && col < m && visited[row][col] == -1 && A[row][col] == 1) {
        return true;
    }

    return false;
}


int rottenOranges(vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();
    vector<vector<int>> visited(n, vector<int>(m, -1));
    int ans = 0;
    queue<Node> q;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (A[row][col] == 2) {
                q.push(Node(row, col, 0));
            }
        }
    }
    int row;
    int col;
    int time;
    while (!q.empty()) {
        Node n = q.front();
        q.pop();
        row = n.row;
        col = n.col;
        time = n.time;
        ans = max(ans, time);

        if (isValid(row - 1, col, visited, A)) {
            q.push(Node(row - 1, col, time + 1));
            A[row - 1][col] = 2;
            visited[row - 1][col] = 1;
        }

        if (isValid(row + 1, col, visited, A)) {
            q.push(Node(row + 1, col, time + 1));
            A[row + 1][col] = 2;
            visited[row + 1][col] = 1;
        }

        if (isValid(row, col - 1, visited, A)) {
            q.push(Node(row, col - 1, time + 1));
            A[row][col - 1] = 2;
            visited[row][col - 1] = 1;
        }

        if (isValid(row, col + 1, visited, A)) {
            q.push(Node(row, col + 1, time + 1));
            A[row][col + 1] = 2;
            visited[row][col + 1] = 1;
        }

    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (A[row][col] == 1) {
                return -1;
            }
        }
    }

    return ans;
}


int main() {
    // vector<vector<int>> edges = { {1, 2},
    //     {2, 3},
    //     {3, 4},
    //     {4, 5} };
    // int A = 5;
    // vector<vector<int>> graph(A + 1);

    // for (auto pair : edges) {
    //     graph[pair[0]].push_back(pair[1]);
    // }
    // vector<int> visited(A + 1, 0);
    // vector<int> path(A + 1, 0);
    // bool res = detectCycle(1, graph, visited, path);
    // cout << res;
    // vector<vector<int>> matrix = {
    //     {1,1,0,0,0},
    //     {0,1,0,0,0},
    //     {1,0,0,1,1},
    //     {0,0,0,0,0},
    //     {1,0,1,0,1}
    // };
    // // output should be 2 
    // int m = matrix.size();
    // int n = matrix[0].size();
    // int island_cnt = 0;
    // vector<vector<int>> visited(m, vector<int>(n, 0));
    // for (int row = 0; row < m; row++) {
    //     for (int col = 0; col < n; col++) {
    //         if (matrix[row][col] == 1 && visited[row][col] == 0) {
    //             cout << "row and col is " << row << col << endl;
    //             island_cnt += 1;
    //             Traversal(row, col, matrix, visited);
    //         }
    //     }
    // }
    // cout << island_cnt;

    // vector<vector<char>> matrix = {
    //     {'X', 'X', 'X', 'X'} ,
    //     {'X', 'O', 'O', 'X'},
    //     {'X', 'X', 'O', 'X'},
    //     {'X', 'O', 'X', 'X'}
    // };

    // solve(matrix);
    // vector<string> A = { "XO", "OX" };
    // int rowlen = (int)A.size();

    // int collen = A[0].size();
    // vector<vector<char>> matrix(rowlen, vector<char>(collen, 'O'));
    // int row = 0;
    // for (int i = 0; i < A.size(); i++) {
    //     for (int j = 0; j < A[i].size(); j++) {
    //         matrix[row][j] = A[row][j];
    //     }
    //     row += 1;
    // }

    vector<vector<int>> A = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    int ans = rottenOranges(A);
    cout << ans;
    return 0;
}