# include<iostream>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;


// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int max_sum(TreeNode* root, int& sum) {
    if (!root) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->val;
    }

    int left = max_sum(root->left, sum);
    int right = max_sum(root->right, sum);

    if (root->left && root->right) {
        sum = max(sum, root->val + left + right);
        return root->val + max(left, right);
    }

    if (root->left) {
        return root->val + left;
    }

    if (root->right) {
        return root->val + right;
    }
}


void Path(TreeNode* root, int target, vector<TreeNode*>& res, vector<TreeNode*>& path) {
    if (root == NULL) {
        return;
    }

    path.push_back(root);
    if (root->val == target) {
        res = path;
        return;
    }
    Path(root->left, target, res, path);
    Path(root->right, target, res, path);
    path.pop_back();

}


int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int left = height(root->left);
    int right = height(root->right);

    return 1 + max(left, right);
}


bool isLeaf(TreeNode* root) {
    if (root->left == NULL && root->right == NULL) {
        return true;
    }

    else {
        return false;
    }
}
TreeNode* buildTree(vector<int> arr) {
    if (arr.size() == 0) {
        return NULL;
    }

    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;


    q.push(root);

    int i = 1;

    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        if (cur == NULL) continue;

        int left_val = arr[i];
        int right_val = arr[i + 1];
        i += 2;

        if (left_val == -1) cur->left = NULL;
        else {
            TreeNode* left_node = new TreeNode(left_val);
            cur->left = left_node;
        }

        if (right_val == -1) cur->right = NULL;
        else {
            TreeNode* right_node = new TreeNode(right_val);
            cur->right = right_node;
        }


        q.push(cur->left);
        q.push(cur->right);
    }

    return root;

}


string can_do_assignments(int schools, int students, int passed) {

    int total_students = schools * students;
    int r = total_students / 2;

    if (passed > r) {
        return "YES";
    }
    else {
        return "NO";
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        string res = can_do_assignments(a, b, c);
        cout << res << endl;
    }


    TreeNode* root = new TreeNode(1);
    TreeNode* n1 = new TreeNode(2);
    TreeNode* n2 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);

    root->left = n1;
    n1->left = n2;
    n2->left = n4;
    n4->left = n5;


    // bool res = isLeaf(n4);
    // cout << res;

    TreeNode* root1 = buildTree(vector<int>{ 1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1 });


    // burning tree
    vector<TreeNode*> path;
    vector<TreeNode*> res;
    int target = 1;
    Path(root, target, res, path);
    int n = res.size();
    vector<int> left_heights(n, 0);
    vector<int> right_heights(n, 0);


    int time = 1;
    int total_time = INT8_MIN;

    for (int i = n - 2; i >= 0; i--) {
        TreeNode* currentNode = res[i];
        left_heights[i] = height(currentNode->left);
        right_heights[i] = height(currentNode->right);
    }


    // for (auto num : left_heights) {
    //     cout << num << "\t";
    // }

    // cout << endl;

    // for (auto num : right_heights) {
    //     cout << num << "\t";
    // }


    // for (int i = n - 2; i >= 0; i--) {
    //     TreeNode* currentNode = res[i];
    //     TreeNode* nextNode = res[i + 1];

    //     if (currentNode->left->val == nextNode->val) {
    //         // TODO  get right height
    //         int total = right_heights[i] + time;
    //         total_time = max(total_time, total);
    //     }

    //     else {
    //         // TODO get left height
    //         int total = left_heights[i] + time;
    //         total_time = max(total_time, total);
    //     }

    //     time += 1;
    // }

    // int h = height(new TreeNode(target));
    // total_time = max(total_time, h - 1);

    // cout << total_time;

    TreeNode* root4 = new TreeNode(2);
    TreeNode* root8 = new TreeNode(-1);
    root4->left = root8;
    int sum = INT8_MIN;
    int val = max_sum(root4, sum);
    cout << val << endl;
    cout << sum << endl;
    return 0;
}