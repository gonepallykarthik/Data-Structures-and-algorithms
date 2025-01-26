#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <queue>
#include <math.h>
using namespace std;



// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


int smallDifference(vector<int> A, vector<int> B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int diff = INT32_MAX;
    int n = A.size();
    int m = B.size();
    int i = 0;
    int j = 0;

    while (i < n && j < m) {
        int curr_diff = abs(A[i] - B[j]);
        if (curr_diff < diff) {
            diff = curr_diff;
        }

        if (A[i] < B[j]) i += 1;
        else j += 1;
    }
    cout << diff;
}

int minimize(const vector<int>& A, const vector<int>& B, const vector<int>& C) {

    int min_diff = INT8_MAX;
    int x = A.size();
    int y = B.size();
    int z = C.size();

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < x && j < y && k < z) {
        int maxi = max(abs(A[i] - B[j]), max(abs(B[j] - C[k]), abs(C[k] - A[i])));
        min_diff = min(min_diff, maxi);

        // get min value of three pointer
        int min_val = min(A[i], min(B[j], C[k]));
        if (min_val == A[i]) {
            i += 1;
        }
        else if (min_val == B[j]) {
            j += 1;
        }
        else {
            k += 1;
        }
    }

    return min_diff;
}


vector<int> topView(TreeNode* root) {
    if (root == NULL) {
        return {};
    }

    map<int, int> mp;
    queue< pair<int, TreeNode*> > q;
    q.push({ 0, root });

    while (!q.empty()) {
        pair<int, TreeNode*> pair = q.front();
        q.pop();

        int level = pair.first;
        TreeNode* node = pair.second;

        if (mp.find(level) == mp.end()) {
            mp[level] = node->val;
        }

        if (node->left != NULL) q.push({ level - 1, node->left });
        if (node->right != NULL) q.push({ level + 1, node->right });
    }
    vector<int> res;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        res.push_back(it->second);
    }

    return res;
}


vector<int> intersection(vector<int> A, vector<int> B) {
    if (A.size() == 0 || B.size() == 0) {
        return {};
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    vector<int> res;
    int i = 0;
    int j = 0;

    while (i < A.size() && j < B.size()) {
        if (A[i] == B[j]) {
            if (res.size() == 0) {
                res.push_back(A[i]);
            }
            else {
                if (res.back() != A[i]) {
                    res.push_back(A[i]);
                }
            }
            i += 1;
        }
        else if (A[i] < B[j]) {
            i += 1;
        }
        else {
            j += 1;
        }
    }

    for (auto num : res) {
        cout << num << "\t";
    }

}







int main() {
    // smallDifference(vector<int>{-1, 5, 10, 20, 28, 3}, vector<int>{26, 134, 135, 15, 17});

    // int res = minimize(vector<int>{1, 4, 10}, vector<int>{2, 15, 20}, vector<int>{10, 12});
    // cout << res;
    // TreeNode* root = new TreeNode(3);
    // TreeNode* n1 = new TreeNode(9);
    // TreeNode* n2 = new TreeNode(20);
    // root->left = n1;
    // root->right = n2;
    // // topView(root);

    // string s = "a";
    // int i = s.size() - 1;
    // while (s[i] == ' ') {
    //     i -= 1;
    // }
    // int length = 0;
    // while (i >= 0 && s[i] != ' ') {
    //     length += 1;
    //     i -= 1;
    // }
    // cout << length;
    // intersection(vector<int>{1, 2, 2, 1}, vector<int>{2, 2});
    // return 0;

}