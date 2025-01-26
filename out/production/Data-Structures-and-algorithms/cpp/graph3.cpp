#include <bits/stdc++.h>
using namespace std;

// example of input 
// A = 3
// B = [[1, 2, 14]
//     [2, 3, 7]
//     [3, 1, 2]]

class DisjointSet {
    vector<int> rank;
    vector<int> parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node]) {
            return node;
        }

        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ul_u = findUPar(u);
        int ul_v = findUPar(v);
        if (ul_v == ul_u) return;
        if (rank[ul_v] < rank[ul_u]) {
            parent[ul_v] = ul_u;
        }
        else if (rank[ul_u] < rank[ul_v]) {
            parent[ul_u] = ul_v;
        }
        else {
            parent[ul_u] = ul_v;
            rank[ul_v] += 1;
        }
    }
};


int Prims(vector<vector<int>>& B, int A) {
    int MOD = static_cast<int>(pow(10, 9) + 7);
    vector<int> visited(A + 1, -1);
    vector<vector<pair<int, int>>> graph(A + 1);
    int n = B.size();
    for (int i = 0; i < n; i++) {
        int src = B[i][0];
        int des = B[i][1];
        int weight = B[i][2];

        graph[src].push_back(make_pair(des, weight));
        graph[des].push_back(make_pair(src, weight));
    }

    priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    visited[1] = 1;

    for (int i = 0; i < graph[1].size(); i++) {
        int node = graph[1][i].first;
        int weight = graph[1][i].second;
        pq.push(make_pair(weight, node));
    }


    int ans = 0;

    while (!pq.empty()) {
        pair<int, int> pair = pq.top();
        pq.pop();
        int weight = pair.first;
        int node = pair.second;
        if (visited[node] == 1) {
            continue;
        }
        visited[node] = 1;
        // cout << "w is" << weight << endl;
        ans += weight;

        // push neighbor nodes
        for (int i = 0; i < graph[node].size(); i++) {
            int new_weight = graph[node][i].second;
            int new_node = graph[node][i].first;
            if (visited[new_node] == -1) {
                pq.push(make_pair(new_weight, new_node));
            }

        }
    }

    return ans % MOD;
}

vector<int> Dijkstra(int A, vector<vector<int> >& B, int C) {
    // C -> src node
    vector<int> distance(A, INT_MAX);
    //                 node weight
    vector<vector<pair<int, int>>> graph(A);
    int n = B.size();
    distance[C] = 0;

    for (int i = 0; i < n; i++) {
        int src = B[i][0];
        int des = B[i][1];
        int weight = B[i][2];

        graph[src].push_back(make_pair(des, weight));
        graph[des].push_back(make_pair(src, weight));
    }


    priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>  > pq;
    pq.push(make_pair(0, C));

    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        int dist = p.first;
        int node = p.second;
        pq.pop();

        for (int i = 0; i < graph[node].size(); i++) {
            int new_node = graph[node][i].first;
            int new_weight = graph[node][i].second;
            if (distance[new_node] > distance[node] + new_weight) {
                distance[new_node] = distance[node] + new_weight;
                pq.push(make_pair(distance[new_node], new_node));
            }
        }
    }


    for (auto num : distance) {
        cout << num << "\t";
    }
    return distance;
}

class myComparator {
public:
    bool operator()(pair< pair<int, int>, pair<int, int>>& a, pair< pair<int, int>, pair<int, int> >& b) {
        return a.first.first < b.first.first;
    }
};

vector<int> EdgeInMST(int A, vector<vector<int>>& B) {

    vector< pair< pair<int, int>, pair<int, int> >> graph;
    int n = B.size();
    vector<int> res(n, 0);

    for (int i = 0; i < n; i++) {
        int src = B[i][0];
        int des = B[i][1];
        int weight = B[i][2];

        graph.push_back({ {weight, i}, {src, des} });
    }
    sort(graph.begin(), graph.end(), myComparator());
    DisjointSet ds(A);

    int i = 0;
    int m = graph.size();
    while (i < m) {
        int j = i;
        while (j < m && graph[j].first.first == graph[i].first.first) {
            if (ds.findUPar(graph[j].second.first) != ds.findUPar(graph[j].second.second)) {
                res[graph[j].first.second] = 1;
            }
            j += 1;
        }

        j = i;
        while (j < m && graph[j].first.first == graph[i].first.first) {
            if (ds.findUPar(graph[j].second.first) != ds.findUPar(graph[j].second.second)) {
                ds.unionByRank(graph[j].second.first, graph[j].second.second);
            }
            j += 1;
        }

        i = j;
    }

    return res;
}

int kruskals(int V, vector<vector<int>> adj[])
{
    // code here

    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < V; i++) {
        for (auto edge : adj[i]) {
            int src = edge[0];
            int des = edge[1];
            int weight = edge[2];

            edges.push_back({ weight, {src, des} });
        }
    }
    int ans = 0;
    DisjointSet ds(V);
    sort(edges.begin(), edges.end());
    for (auto edge : edges) {
        int weight = edge.first;
        int src = edge.second.first;
        int des = edge.second.second;

        if (ds.findUPar(src) != ds.findUPar(des)) {
            ans += weight;
            ds.unionByRank(src, des);
        }
    }

    return ans;
}



int main() {
    // cout << "welcome to this applicaton";
    // int A = 3;
    // vector<vector<int>> B = {
    //     {1, 2, 14},
    //     {2, 3, 7},
    //     {3, 1, 2}
    // };
    // int ans = Prims(B, A);
    // cout << ans;
    // int A = 6;
    // vector<vector<int>> B = {
    //     {0, 4, 9},
    //     {3, 4, 6},
    //     {1, 2, 1},
    //     {2, 5, 1},
    //     {2, 4, 5},
    //     {0, 3, 7},
    //     {0, 1, 1},
    //     {4, 5, 7},
    //     {0, 5, 1}
    // };
    // int C = 4;
    // Dijkstra(A, B, C);

    int A = 3;
    vector<vector<int>> B = {
        {1, 2, 2},
        {1, 3, 2},
        {2, 3, 3}
    };
    vector<int> res = EdgeInMST(A, B);
    for (auto num : res) {
        cout << num << "\t";
    }
    return 0;
}