#include <bits/stdc++.h>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* dfs(Node* node, map<Node*, Node*>& mp) {
    if (mp.find(node) != mp.end()) {
        return mp[node];
    }
    Node* newNode = new Node(node->val);
    mp[node] = newNode;

    for (auto neighbor : node->neighbors) {
        newNode->neighbors.push_back(dfs(neighbor, mp));
    }

    return newNode;
}

Node* cloneGraph(Node* node) {
    map<Node*, Node*> mp;
    return dfs(node, mp);
}



vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> visited(numCourses, -1);
    vector<int> InDegree(numCourses, 0);
    vector<vector<int>> graph(numCourses);
    int n = prerequisites.size();
    for (int i = 0; i < n; i++) {
        int node = prerequisites[i][0];
        int adjNode = prerequisites[i][1];
        InDegree[node] += 1;

        graph[node].push_back(adjNode);
        graph[adjNode].push_back(node);
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < InDegree.size(); i++) {
        if (InDegree[i] == 0) {
            pq.push(i);
        }
    }
    vector<int> res(numCourses, -1);
    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();
        res[node] = node;
        if (visited[node] == 1) {
            continue;
        }
        visited[node] = 1;

        for (int i = 0; i < graph[node].size(); i++) {
            int newNode = graph[node][i];
            InDegree[newNode] -= 1;
            if (InDegree[newNode] == 0) {
                if (visited[newNode] == -1) pq.push(newNode);
            }
        }
    }
    for (auto edge : res) {
        if (edge == -1) {
            return {};
        }
    }
    return res;
}
bool dfs_traversal(int src, int des, vector<vector<int>>& graph, vector<int>& visited) {
    visited[src] = 1;
    if (src == des) {
        return true;
    }

    for (auto neighbor : graph[src]) {
        if (visited[neighbor] == -1) {
            if (dfs_traversal(neighbor, des, graph, visited)) {
                return true;
            }
        }
    }

    return false;
}


bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<vector<int>> graph(n);
    vector<int> visited(n, -1);
    for (auto edge : edges) {
        int src = edge[0];
        int des = edge[1];
        graph[src].push_back(des);
        graph[des].push_back(src);
    }
    return dfs_traversal(source, destination, graph, visited);
}
int findJudge(int n, vector<vector<int>>& trust) {
    vector<vector<int>> graph(n + 1);
    for (auto edge : trust) {
        graph[edge[0]].push_back(edge[1]);
    }

    int trusted_person = -1;
    for (int i = 1; i <= n; i++) {
        if (graph[i].size() == 0) {
            trusted_person = i;
        }
    }

    if (trusted_person == -1)return -1;
    vector<int> nodes = graph[trusted_person];
    for (auto node : nodes) {
        bool trust = false;
        for (int i = 1; i <= n; i++) {
            if (i == node) trust = true;
        }
        if (trust == false) return -1;
    }

    return trusted_person;
}

bool DFS_Traversal(int src, vector<int>& visited, vector<int>& path, vector<vector<int>>& graph) {
    visited[src] = 1;
    path[src] = 1;
    for (auto neighbor : graph[src]) {
        if (path[neighbor] == 1) {
            return true;
        }
    }

    for (auto neighbor : graph[src]) {
        if (visited[neighbor] == -1) {
            if (DFS_Traversal(neighbor, visited, path, graph)) {
                return true;
            }
        }
    }

    path[src] = 0;
    visited[src] = -1;
    return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> visited(n, -1);
    vector<int> path(n, 0);
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (visited[i] == -1) {
            if (DFS_Traversal(i, visited, path, graph) == false) {
                res.push_back(i);
            }
        }
    }

    return res;
}
void Traversal(int node, vector<vector<int>>& graph, vector<int>& informTime, int& ans, int& maxi, vector<int>& visited) {
    visited[node] = 1;
    maxi = max(ans, maxi);

    for (auto neighbor : graph[node]) {
        if (visited[neighbor] == -1) {
            ans += informTime[node];
            Traversal(neighbor, graph, informTime, ans, maxi, visited);
            ans -= informTime[node];
        }
    }
}

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
    vector<vector<int>> graph(n);
    vector<int> visited(n, -1);
    for (int i = 0; i < n; i++) {
        if (manager[i] != -1) {
            graph[manager[i]].push_back(i);
        }
    }
    int ans = 0;
    int maxi = 0;
    Traversal(headID, graph, informTime, ans, maxi, visited);
    return maxi;
}
int dfstraversal(int node, int cost, vector<vector<int>>& graph, vector<int>& visited, vector<bool>& hasApple) {
    if (visited[node] == 1) {
        return 0;
    }
    visited[node] = 1;
    int childCost = 0;
    for (auto neighbor : graph[node]) {
        childCost += dfstraversal(neighbor, 2, graph, visited, hasApple);
    }
    if (childCost == 0 && !hasApple[node]) {
        return 0;
    }

    return cost + childCost;
}

int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
    vector<vector<int>> graph(n);
    int m = edges.size();
    for (int i = 0; i < m; i++) {
        int src = edges[i][0];
        int des = edges[i][1];
        graph[src].push_back(des);
        graph[des].push_back(src);
    }
    vector<int> visited(n, -1);
    return dfstraversal(0, 0, graph, visited, hasApple);
}

int main() {
    // cout << "welcome";
    // int numCourses = 4;
    // vector<vector<int>> prerequisites = { {1, 0}, {2, 0}, {3, 1}, {3, 2} };
    // findOrder(numCourses, prerequisites);

    // int n = 6;
    // vector<vector<int>> edges = { {0,1} ,{0,2} ,{3,5} ,{5,4}, {4,3} };
    // int source = 0;
    // int destination = 5;
    // bool r = validPath(n, edges, source, destination);
    // cout << r;

    // int n = 3;
    // vector<vector<int>> edges = { {1,2}, {2,3} };
    // int res = findJudge(n, edges);
    // cout << res;

    // vector<vector<int>> graph = { {1, 2}, {2, 3}, {5}, {0}, {5}, {}, {} };
    // vector<int> res = eventualSafeNodes(graph);
    // for (auto num : res) {
    //     cout << num << "\t";
    // }
    // int n = 6;
    // int headID = 2;
    // vector<int> manager = { 2, 2, -1, 2, 2, 2 };
    // vector<int> informTime = { 0, 0, 1, 0, 0, 0 };
    // int minutes = numOfMinutes(n, headID, manager, informTime);
    // cout << minutes << endl;
    int n = 7;
    vector<vector<int>> edges = { {0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6} };
    vector<bool> apples = { false, false, true, false, true, true, false };
    minTime(n, edges, apples);
    return 0;
}