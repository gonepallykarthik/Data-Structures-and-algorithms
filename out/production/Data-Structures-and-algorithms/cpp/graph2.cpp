#include <bits/stdc++.h>
using namespace std;

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

vector<int> bfsOfGraph(int V, vector<int> adj[]) {
    // Code here
    vector<int> visited(V, -1);
    visited[0] = 1;
    queue<int> q;
    q.push(0);
    vector<int> res;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        res.push_back(v);
        for (auto neighbor : adj[v]) {
            if (visited[neighbor] == -1) {
                visited[neighbor] = 1;
                q.push(neighbor);
            }
        }
    }

    return res;
}

void flipkartDeliveryOptimization(vector<vector<int>>& grid) {
    queue<Node> q;
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, -1));

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (grid[row][col] == 1) {
                visited[row][col] = 1;
                grid[row][col] = 0;
                q.push(Node(row, col, 0));
            }
        }
    }

    while (!q.empty()) {
        Node v = q.front();
        q.pop();

        vector<int> dr = { -1,0,1,0,-1,-1,1,1 };
        vector<int> dc = { 0,-1,0,1,-1,1,-1,1 };
        for (int i = 0; i < 8; i++) {
            int newrow = v.row + dr[i];
            int newcol = v.col + dc[i];
            if (newrow >= 0 and newrow < n and newcol >= 0 && newcol < m && visited[newrow][newcol] == -1) {
                visited[newrow][newcol] = 1;
                grid[newrow][newcol] = v.time + 1;
                q.push(Node(newrow, newcol, v.time + 1));
            }
        }
    }
}

vector<int> topologicalSort(int A, vector<vector<int> >& B) {
    vector<int> inDegree(A + 1, 0);
    int n = B.size();

    for (int i = 0; i < n; i++) {
        int node = B[i][1];
        inDegree[node] += 1;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= A; i++) {
        if (inDegree[i] == 0) {
            pq.push(i);
        }
    }
    vector<int> res;
    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();
        res.push_back(node);
        for (int i = 0; i < n; i++) {
            if (B[i][0] == node) {
                inDegree[B[i][1]] -= 1;
                if (inDegree[B[i][1]] == 0) {
                    pq.push(B[i][1]);
                }
            }
        }
    }

    return res;

}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> inDegree(numCourses, 0);
    int n = prerequisites.size();

    for (int i = 0; i < n; i++) {
        int node = prerequisites[i][1];
        inDegree[node] += 1;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < inDegree.size(); i++) {
        if (inDegree[i] == 0) {
            pq.push(i);
        }
    }

    if (pq.empty()) return false;

    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();
        for (int i = 0; i < n; i++) {
            if (prerequisites[i][0] == node) {
                inDegree[prerequisites[i][1]] -= 1;
                if (inDegree[prerequisites[i][1]] == 0) {
                    pq.push(prerequisites[i][1]);
                }
            }
        }
    }
    for (auto num : inDegree) {
        if (num != 0) {
            return false;
        }
    }
    return true;
}
// B = [
//[2, 5, 1]
// [1, 3, 1]
// [0, 5, 2]
// [0, 2, 2]
// [1, 4, 1]
// [0, 1, 1]]

int anotherBFS(int A, vector<vector<int> >& B, int C, int D) {
    //   node            pair-> neighbor, weight     
    map<int, vector<pair<int, int>>> mp;
    int n = B.size();
    int m = B[0].size();
    int max_value = -1;
    int temp = A;
    // undirected if there is a edge from 2 -> 5 then there is also edge from 5 -> 2
    for (vector<int> info : B) {
        int startNode = info[0];
        int endNode = info[1];
        int weight = info[2];
        if (weight == 1) {
            mp[startNode].push_back(make_pair(endNode, weight));
            mp[endNode].push_back(make_pair(startNode, weight));
        }
        else {
            mp[startNode].push_back(make_pair(temp, 1));
            mp[temp].push_back(make_pair(startNode, 1));

            mp[endNode].push_back(make_pair(temp, 1));
            mp[temp].push_back(make_pair(endNode, 1));
            temp += 1;
            max_value = max(max_value, temp);
        }
    }

    int src = C;
    int des = D;
    if (src == des) return 0;
    queue<int> q;
    q.push(src);
    vector<int>distance(max_value, 0);
    set<int> s;
    s.insert(src);
    distance[src] = 0;


    while (!q.empty()) {
        int node = q.front();
        q.pop();
        vector<pair<int, int>> neighborNodes = mp[node];
        for (auto pair : neighborNodes) {
            int newnode = pair.first;
            if (s.find(newnode) == s.end()) {
                s.insert(newnode);
                int weight = pair.second;
                distance[newnode] = distance[node] + weight;
                if (newnode == des) {
                    return distance[newnode];
                }
                q.push(newnode);
            }
        }
    }



    if (distance[des] == 0) {
        return -1;
    }
    return distance[des];

    // for (auto num : distance) {
    //     cout << num << "\t";
    // }
    // cout << endl;

    // for (auto it = mp.begin(); it != mp.end(); it++) {
    //     cout << it->first << "\t";
    //     for (auto pair : it->second) {
    //         cout << pair.first << pair.second << "\t";
    //     }
    //     cout << endl;
    // }
}



int main() {

    // cout << "welcome to this application";
    vector<vector<int>> warehouse = {
        {0,0,0,0,1,0,0,1,0},
        {0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1},
    };

    // flipkartDeliveryOptimization(warehouse);

    // for (int row = 0; row < warehouse.size(); row++) {
    //     for (int col = 0; col < warehouse[0].size(); col++) {
    //         cout << warehouse[row][col] << "\t";
    //     }

    //     cout << endl;
    // }
    // vector<vector<int>> B = {
    //     {0,1},
    //     {0,2},
    //     {1,3},
    //     {1,4},
    //     {3,4}
    // };
    // vector<int> res = topologicalSort(6, B);
    // for (auto num : res) {
    //     cout << num << "\t";
    // }

    // bool r = canFinish(5, B);
    // cout << r;
    vector<vector<int>> B = {
        {3,11,2},
        {5,12,1},
        {0,7,2},
        {5,6,2},
        {6,10,1},
        {5,9,1},
    };
    int ans = anotherBFS(13, B, 9, 4);
    cout << ans;
    return 0;
}