#include <bits/stdc++.h>
using namespace std;


//  Definition for binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
int Traverse(TreeNode* root, int& currentSum, int target) {
    currentSum += root->val;

    if (root->left == NULL && root->right == NULL) {
        if (currentSum == target) {
            return 1;
        }

        return 0;
    }

    int left = Traverse(root->left, currentSum, target);
    int right = Traverse(root->right, currentSum, target);

    return left || right;
}

int hasPathSum(TreeNode* A, int B) {
    if (A == NULL) return 0;
    int currentSum = A->val;
    if (currentSum == B) return 1;

    if (A->left != NULL && A->right != NULL) {
        return Traverse(A->left, currentSum, B) || Traverse(A->right, currentSum
            , B);
    }

}

class customSort {
public:
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        int aValue = a.first;
        int aWeight = a.second;
        int bValue = b.first;
        int bWeight = b.second;

        double r1 = (double)aValue / (double)aWeight;
        double r2 = (double)bValue / (double)bWeight;

        return r1 > r2;
    }
};


double fractionalKnapsack(vector<int> A, vector<int> B, int C) {
    vector<pair<int, int>> items;
    for (int i = 0; i < A.size(); i++) {
        items.push_back(make_pair(A[i], B[i]));
    }
    sort(items.begin(), items.end(), customSort());

    double final_ans = 0;
    int curr_weight = 0;
    int n = items.size();
    for (int i = 0; i < n; i++) {
        if (curr_weight + items[i].second <= C) {
            final_ans += items[i].first;
            curr_weight += items[i].second;
        }
        // take fraction part
        else {
            int rem = C - curr_weight;
            final_ans += ((double)(items[i].first / (double)items[i].second)) * (double)rem;
            break;
        }
    }

    return final_ans;
}



int main() {
    int arr[] = { 10, 2, 30, 7, 5 };
    int size = 5; // Size of the array
    int k = 3;

    priority_queue<int> pq;
    for (int i = 0; i < k; i++) {
        pq.push(arr[i]);
    }

    for (int i = k; i < size; i++) {
        int curr = arr[i];
        if (curr < pq.top()) {
            pq.pop();
            pq.push(curr);
        }
    }

    // cout << pq.top();
    double ans = fractionalKnapsack({ 3 }, { 20 }, 17);
    cout << "ans is " << ans;
    cout << ans * 100;
    return 0;
}

