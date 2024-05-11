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


int main() {
    // cout << "welcome";
    int numCourses = 4;
    vector<vector<int>> prerequisites = { {1, 0}, {2, 0}, {3, 1}, {3, 2} };
    findOrder(numCourses, prerequisites);
    return 0;
}