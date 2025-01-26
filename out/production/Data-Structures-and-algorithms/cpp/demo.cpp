#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;


//   Definition for binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// using iterative approach not recursion
vector<int> inOrderTraversal(TreeNode* root) {
    if (root == NULL) {
        return vector<int>{};
    }

    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr != NULL || !st.empty()) {
        if (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        }
        else {
            TreeNode* node = st.top();
            st.pop();
            curr = node;
            res.push_back(curr->val);
            curr = curr->right;
        }
    }

    return res;
}


void preorderTraversal(TreeNode* A, vector<int>& res) {

    if (A == NULL) {
        return;
    }
    res.push_back(A->val);
    preorderTraversal(A->left, res);
    preorderTraversal(A->right, res);
}

TreeNode* construct(vector<int>& In, vector<int>& pos, int ps, int pe, int is, int ie, map<int, int>& mp) {
    if (ps > pe || is > ie) {
        return NULL;
    }


    int root_val = pos[pe];
    TreeNode* root = new TreeNode(root_val);

    // map <int,int> key ->number and value -> idx
    int idx = mp[root_val];

    int left_subarray_len = idx - is;

    // construct left and right sub trees
    root->left = construct(In, pos, ps, ps + left_subarray_len - 1, is, idx - 1, mp);

    root->right = construct(In, pos, ps + left_subarray_len, pe - 1, idx + 1, ie, mp);

    return root;
}





int main() {
    cout << "welcome to this application " << endl;
    vector<int> nums = { 1,2,3,5,6,10 };
    map<int, int> mp;

    for (int i = 0; i < nums.size(); i++) {
        mp.insert({ nums[i], i });
    }

    // for (auto it = mp.begin(); it != mp.end(); it++) {
    //     cout << it->first << it->second << endl;
    // }
    int root_val = 2;
    cout << mp[root_val];
    return 0;
}