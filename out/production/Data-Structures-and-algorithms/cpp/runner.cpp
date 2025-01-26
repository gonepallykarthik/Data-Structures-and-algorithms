#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node* left, * right;
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

struct TreeInfo
{
    bool possible;
    int sum;

    TreeInfo(bool poss, int _sum) {
        possible = poss;
        sum = _sum;
    }
};

TreeInfo* validate(Node* root) {
    if (!root) {
        return new TreeInfo(true, 0);
    }

    if (root->left == NULL && root->right == NULL) {
        return new TreeInfo(true, root->data);
    }

    TreeInfo* left = validate(root->left);
    TreeInfo* right = validate(root->right);

    if (left->possible && right->possible && left->sum + right->sum == root->data) {
        return new TreeInfo(true, left->sum + right->sum + root->data);
    }

    return new TreeInfo(false, left->sum + right->sum + root->data);
}

bool isSumTree(Node* root) {
    if (!root) {
        return true;
    }

    if (root->left == NULL && root->right == NULL) {
        return true;
    }

    TreeInfo* res = validate(root);
    return res->possible;
}

int isSameTree(Node* A, Node* B) {
    if (A == NULL && B == NULL) {
        return true;
    }

    if (A == NULL || B == NULL) {
        return false;
    }

    if (A->data != B->data) {
        return false;
    }

    return isSameTree(A->left, B->left) && isSameTree(A->right, B->right);

}


int solve(vector<int> A) {
    if (A.size() == 0) {
        return -1;
    }
    int ans = INT_MAX;
    int n = A.size();

    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int currentNUm = A[i];
        if (mp.find(currentNUm) != mp.end()) {
            int distance = i - mp[currentNUm];
            ans = min(ans, distance);
        }

        mp.insert({ A[i], i });
    }
    return ans;
}

int LongestSubarraySumZero(vector<int> A) {
    if (A.size() == 0) {
        return 0;
    }
    int n = A.size();
    int ans = 0;
    map<int, int> mp;
    mp.insert({ 0,-1 });
    int prefix_sum = 0;

    for (int i = 0; i < n; i++) {
        prefix_sum += A[i];
        if (mp.find(prefix_sum) != mp.end()) {
            ans = max(ans, (i - mp[prefix_sum]));
        }

        mp[prefix_sum] = i;
    }

    return ans;
}


int main() {
    // int res = INT_MIN;
    // Node* root = new Node(3);
    // Node* n1 = new Node(2);
    // Node* n2 = new Node(1);

    // root->left = n1;
    // root->right = n2;

    // isSumTree(root);
    // int ans = solve(vector<int>{1, 1});
    // cout << ans;
    int ans = LongestSubarraySumZero(vector<int>{1, -2, 1, 2});
    return ans;
    return 0;
}