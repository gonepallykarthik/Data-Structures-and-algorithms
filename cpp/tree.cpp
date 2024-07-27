#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};


//  Definition for binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};




class BSTIterator {
public:
    vector<int> in_order;
    int idx;
    BSTIterator(TreeNode* root) {
        this->idx = 0;
        this->InorderTraversal(root, in_order);
    }

    int next() {
        int ele = this->in_order[idx];
        this->idx += 1;
        return ele;
    }

    bool hasNext() {
        if (this->idx >= in_order.size()) return false;

        return true;
    }

    void InorderTraversal(TreeNode* root, vector<int>& res) {
        if (root == NULL) return;

        InorderTraversal(root->left, res);
        res.push_back(root->val);
        InorderTraversal(root->right, res);
    }
};




int subarraysWithKDistinct(vector<int> nums, int k) {
    if (nums.size() == 0) {
        return 0;
    }
    map<int, int> mp;
    int left_far = 0;
    int left_near = 0;
    int res = 0;

    for (int right = 0; right < nums.size(); right++) {
        int currentNum = nums[right];
        mp[currentNum] += 1;

        // if we have have extra's at left
        while (mp[nums[left_near]] > 1) {
            mp[nums[left_near]] -= 1;
            left_near += 1;
        }

        // if it is not a valid window
        while (mp.size() > k) {
            mp[nums[left_near]] -= 1;
            if (mp[nums[left_near]] == 0) mp.erase(nums[left_near]);
            left_near += 1;
            left_far = left_near;
        }

        // if it is a valid window 
        if (mp.size() == k) {
            res += left_near - left_far + 1;
        }
    }


    return res;
}


void KthLargestElement(Node* root, int k, int& ans) {
    if (!root) {
        return;
    }

    KthLargestElement(root->right, k, ans);
    k--;
    ans = root->data;
    if (k <= 0) {
        return;
    }

    KthLargestElement(root->left, k, ans);
}

int solve(TreeNode* A, int B) {
    if (A == NULL) {
        return 0;
    }

    TreeNode* cur = A;
    while (cur) {
        if (cur->val == B) return 1;

        else if (cur->val > B) {
            cur = cur->left;
        }
        else cur = cur->right;
    }

    return 0;
}

int ValidBST(TreeNode* A, int min_val, int max_val) {
    if (A == NULL) {
        return 1;
    }

    else if (A->val < min_val || A->val > max_val) return 0;

    return ValidBST(A->left, min_val, A->val) && ValidBST(A->right, A->val, max_val);
}

TreeNode* constructBST(const vector<int>& A, int left, int right) {
    if (left > right) {
        return NULL;
    }

    int mid = (left + right) / 2;
    TreeNode* root = new TreeNode(A[mid]);
    root->left = constructBST(A, left, mid - 1);
    root->right = constructBST(A, mid + 1, right);

    return root;
}


TreeNode* deleteNode(TreeNode* root, int target) {
    if (root == NULL) {
        // TODO
        return NULL;
    }

    if (root->val == target) {

        //case 1
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        }

        // case 2 only one child exits
        else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        else if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }

        // case 3
        else {
            // find largest node in leftSubTree
            TreeNode* child = root->left;
            TreeNode* parent = root;
            while (child->right != NULL) {
                parent = child;
                child = child->right;
            }

            // check if child and parent points to same node
            if (root == parent) {
                child->right = root->right;
                delete root;
                return child;
            }

            else {
                parent->right = child->left;
                child->left = root->left;
                child->right = root->right;
                delete root;
                return child;
            }

        }

    }

    else if (root->val > target) {
        root->left = deleteNode(root->left, target);
        return root;
    }

    else {
        root->right = deleteNode(root->right, target);
        return root;
    }

}


int TwoSumBST(TreeNode* root, int target) {
    if (!root) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 0;
    }


    set<int> st;
    stack<TreeNode*> stack1;
    TreeNode* curr = root;
    while (curr != NULL || stack1.size() > 0) {
        if (curr != NULL) {
            stack1.push(curr);
            curr = curr->left;
        }

        else {
            TreeNode* topEle = stack1.top();
            stack1.pop();

            int complement = target - topEle->val;
            if (st.find(complement) != st.end()) {
                return 1;
            }

            st.insert(topEle->val);
            curr = topEle->right;

        }
    }
    return 0;
}


int main() {
    // cout << "welcome to the application" << endl;
    // int r = subarraysWithKDistinct(vector<int>{1, 2, 1, 3, 4}, 3);
    // cout << r << endl;
    // string str = "Hello World";
    // cout << str.size();
    // int a = 10;
    // int b = 20;
    // a = a ^ b;
    // b = a ^ b;
    // a = a ^ b;
    // cout << a << "\t" << b << endl;
    cout << 0 || 0;
    return 0;
}