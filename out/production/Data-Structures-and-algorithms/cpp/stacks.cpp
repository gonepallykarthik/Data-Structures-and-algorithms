#include <bits/stdc++.h>
using namespace std;

int largestRectangleArea(vector<int>& heights) {
    if (heights.size() == 0) {
        return -1;
    }
    int n = heights.size();
    vector<int> leftSmall(n, 0);
    vector<int> rightSmall(n, 0);
    stack<int> st1;
    st1.push(0);

    for (int i = 1; i < n; i++) {
        int current = heights[i];
        while (!st1.empty() && heights[st1.top()] >= current) {
            st1.pop();
        }
        if (st1.empty()) {
            leftSmall[i] == 0;
        }
        else {
            leftSmall[i] = st1.top() + 1;
        }
        st1.push(i);
    }

    stack<int> st2;
    st2.push(n - 1);

    for (int i = n - 2; i >= 0; i--) {
        int current = heights[i];
        while (!st2.empty() && heights[st2.top()] >= current) {
            st2.pop();
        }
        if (st2.empty()) {
            rightSmall[i] == 0;
        }
        else {
            rightSmall[i] = st2.top() + 1;
        }
        st2.push(i);
    }

    int ans = -1e9;
    for (int i = 0; i < n; i++) {
        int r = (rightSmall[i] - leftSmall[i] - 1) * heights[i];
        ans = max(ans, r);
    }
    cout << ans;
    return ans;
}

bool isPossible(int N, int P, vector<pair<int, int> >& prerequisites) {
    // Code here
    vector<int> inDegree(N, 0);
    vector<vector<int>> graph(N);

    for (auto pair : prerequisites) {
        graph[pair.second].push_back(pair.first);
        inDegree[pair.first] += 1;
    }



    priority_queue<int> pq;
    for (int i = 0; i < inDegree.size(); i++) {
        if (inDegree[i] == 0) {
            pq.push(i);
        }
    }

    if (pq.empty() == true) {
        return false;
    }

    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();

        for (auto neighbor : graph[node]) {
            inDegree[neighbor] -= 1;
            if (inDegree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }

    for (int i = 0; i < inDegree.size(); i++) {
        cout << inDegree[i] << "\t";
    }

    return true;
}

string findOrder(string dict[], int N, int K) {
    //code here
    vector<vector<int>> graph(K);
    vector<int> inDegree(K, 0);

    for (int i = 1; i < N; i++) {
        string first = dict[i - 1];
        string second = dict[i];
        int idx1 = 0;
        int idx2 = 0;
        while (idx1 < first.size() && idx2 < second.size()) {
            if (first[idx1] != second[idx2]) {
                int f = first[idx1] - 97;
                int s = second[idx2] - 97;
                inDegree[s] += 1;
                graph[f].push_back(s);
                break;
            }
            else {
                idx1 += 1;
                idx2 += 1;
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < inDegree.size(); i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    string res = "";
    while (!q.empty()) {
        int ele = q.front();
        char c = static_cast<char>(ele + 97);
        res.push_back(c);
        q.pop();

        for (auto neighbor : graph[ele]) {
            inDegree[neighbor] -= 1;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    cout << res;
    return res;
}

bool isBipartite(int V, vector<int>adj[]) {
    // Code here
    vector<int> graphColor(V, -1);
    queue<pair<int, int>> q;
    //pair ->        n  c
    graphColor[0] = 1;
    q.push(make_pair(0, 1));

    while (!q.empty()) {
        int node = q.front().first;
        int color = q.front().second;
        q.pop();

        int newColor = !color;
        for (auto neighbor : adj[node]) {
            cout << graphColor[0] << graphColor[1] << graphColor[2] << endl;
            if (graphColor[neighbor] != -1) {
                if (graphColor[neighbor] == color) {
                    return false;
                }
            }

            else {
                graphColor[neighbor] = newColor;
                q.push(make_pair(neighbor, newColor));
            }
        }
    }

    return true;
}


int ParallelCourses(vector<vector<int>> pre, int N) {
    vector<int> inDegree(N + 1, 0);
    vector<vector<int>> graph(N + 1);
    int n = pre.size();
    for (int i = 0; i < n; i++) {
        int f = pre[i][0];
        int s = pre[i][1];
        graph[f].push_back(s);
        inDegree[s] += 1;
    }

    queue<int> q;
    for (int i = 1; i < inDegree.size(); i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    if (q.empty()) {
        return -1;
    }

    int ans = 0;
    while (!q.empty()) {
        int size = q.size();
        ans += 1;
        for (int i = 0; i < size; i++) {
            int node = q.front();
            q.pop();

            for (auto neighbor : graph[node]) {
                inDegree[neighbor] -= 1;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
    }

    return ans;
}

// n = 3, relations = [[1, 3], [2, 3]], time = [3, 2, 5]
int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
    if (relations.size() == 0) {
        return 0;
    }
    vector<vector<int>> graph(n);
    vector<int> deg(n, 0);
    vector<int> ct(n, 0);

    for (int i = 0; i < relations.size(); i++) {
        int first = relations[i][0] - 1;
        int second = relations[i][1] - 1;
        graph[first].push_back(second);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            deg[graph[i][j]] += 1;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (auto neighbor : graph[node]) {
            deg[neighbor] -= 1;
            if (deg[neighbor] == 0) {
                q.push(neighbor);
            }
            ct[neighbor] = max(ct[neighbor], ct[node] + time[node]);
        }

    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, ct[i] + time[i]);
    }
    cout << ans;
    return ans;

}


int main() {
    vector<int> nums = { 2,1,5,6,2,3 };
    // largestRectangleArea(nums);
    vector<pair<int, int>> preq = {
        {1,0},
        {2,1},
        {3,2}
    };
    // isPossible(4, 3, preq);
    // string dict[] = { "caa", "aaa", "aab" };
    // findOrder(dict, 3, 3);
    // cout << 'a' - 97;
    vector<int> adj[] = {
        {1} ,
        {0,2},
        {1}
    };
    // cout << isBipartite(3, adj);
    int N = 3;
    vector<vector<int>> relations = { {1,3}, {2, 3} };
    // cout << ParallelCourses(relations, N);
    vector<int> time = { 3,2,5 };
    cout << minimumTime(N, relations, time);
    return 0;
}