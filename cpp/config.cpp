#include<bits/stdc++.h>
using namespace std;


//  Definition for binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct CustomComp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {

        return a.second > b.second;
    }
};

// Structure of node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

int getDistance(TreeNode* root, int target) {
    if (root->val == target)
    {
        return 0;
    }
    if (root->val > target) {
        return 1 + getDistance(root->left, target);
    }

    return 1 + getDistance(root->right, target);
}

int preTraverse(TreeNode* root, int target1, int target2) {
    if (!root) {
        return 0;
    }

    if (root->val > target1 && root->val > target2) {
        return preTraverse(root->left, target1, target2);
    }

    else if (root->val < target1 && root->val < target2)
    {
        return preTraverse(root->right, target1, target2);
    }
    else {
        return getDistance(root, target1) + getDistance(root, target2);
    }

    return 0;

}

vector<int> maxSubsequence(vector<int> nums, int k) {
    if (nums.size() == 0) {
        return {};
    }
    vector<int> res;
    priority_queue<pair<int, int>> pq;

    for (int i = 0; i < nums.size(); i++) {
        pq.push({ nums[i], i });
    }

    int cnt = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, CustomComp> p;

    while (cnt < k && !pq.empty()) {
        pair<int, int> pair = pq.top();
        p.push(pair);
        cnt += 1;
        pq.pop();
    }

    while (!p.empty()) {
        res.push_back(p.top().first);
        p.pop();
    }

    return res;
}

bool isValidString(int idx, int openCnt, const string& s, vector<vector<int>>& memo) {

    if (idx == s.size()) {
        return (openCnt == 0);
    }

    if (memo[idx][openCnt] != -1) {
        return memo[idx][openCnt];
    }

    bool isValid = false;
    if (s[idx] == '*') {
        // first treat it as '('
        isValid |= isValidString(idx + 1, openCnt + 1, s, memo);

        if (openCnt) {
            isValid |= isValidString(idx + 1, openCnt - 1, s, memo);
        }
        isValid |= isValidString(idx + 1, openCnt, s, memo);
    }

    // if it is not '*'
    else {
        if (s[idx] == '(') {
            isValid = isValidString(idx + 1, openCnt + 1, s, memo);
        }
        else if (openCnt) {
            isValid = isValidString(idx + 1, openCnt - 1, s, memo);
        }

    }

    return memo[idx][openCnt] = isValid;

}



bool hasPathSum(TreeNode* root, int B, int current_sum) {
    current_sum += root->val;
    if (root->left == NULL && root->right == NULL && current_sum == B) {
        return true;
    }

    if (root->left) hasPathSum(root->left, B, current_sum);
    if (root->right) hasPathSum(root->right, B, current_sum);
}

struct TreeInfo {
    bool isHeap;
    int data;

    TreeInfo(bool h, int d) {
        isHeap = h;
        data = d;
    }
};

int CountNodes(Node* root) {
    if (!root) {
        return 0;
    }

    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

TreeInfo* validate(Node* root, int idx, int node_cnt) {
    if (!root) {
        return new TreeInfo(true, -1);
    }

    TreeInfo* left = validate(root->left, 2 * idx + 1, node_cnt);
    TreeInfo* right = validate(root->right, 2 * idx + 2, node_cnt);

    bool isH = left->isHeap && right->isHeap;

    if (left->data > root->data || right->data > root->data || idx >= node_cnt) {
        isH = false;
    }

    return new TreeInfo(isH, root->data);
}


bool isHeap(struct Node* tree) {
    // code here
    int node_cnt = CountNodes(tree);
    TreeInfo* res = validate(tree, 0, node_cnt);
    return res->isHeap;
}

// 1 40 2 3 

vector<int> nearlySortedArray(vector<int>& A, int B) {
    if (A.size() == 0) {
        return {};
    }
    int n = A.size();
    vector<int> ans;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < B + 1; i++) {
        pq.push(A[i]);
    }

    for (int j = B + 1; j < n; j++) {
        ans.push_back(pq.top());
        pq.pop();
        pq.push(A[j]);
    }

    while (!pq.empty()) {
        ans.push_back(pq.top());
        pq.pop();
    }

    return ans;
}

vector<int> solve(int A, vector<int> B) {
    if (B.size() == 0) {
        return {};
    }
    priority_queue<int, vector<int>, greater<int>> pq;

    vector<int> ans;
    int idx = 0;
    while (idx <= A - 2) {
        ans.push_back(-1);
        pq.push(B[idx]);
        idx += 1;
    }


    pq.push(B[idx]);
    ans.push_back(pq.top());
    idx += 1;

    while (idx < B.size()) {
        int currEle = B[idx];
        if (pq.top() < currEle) {
            pq.pop();
            pq.push(currEle);
        }

        ans[idx] = pq.top();
        idx += 1;
    }



    for (auto num : ans) {
        cout << num << "\t";
    }
    return ans;

}

vector<int> Median(vector<int>& A) {
    if (A.size() == 0) {
        return {};
    }

    priority_queue<int> h1;    //max_heap
    priority_queue<int, vector<int>, greater<int>> h2;  // min_heap

    int n = A.size();
    vector<int> ans;
    for (int i = 0; i < n; i++) {

        // if it is a first Element
        if (i == 0) {
            h1.push(A[i]);
            ans.push_back(h1.top());
            continue;
        }

        // decide whether to place element in first heap or second heap
        if (A[i] > h1.top()) {  // then place it in second heap
            h2.push(A[i]);
        }
        else { // place it in first heap
            h1.push(A[i]);
        }

        int diff = h1.size() - h2.size();
        if (diff == 0) {
            // calculate median
            ans.push_back(h1.top());
        }
        else if (diff == 1) {
            ans.push_back(h1.top());
        }

        else if (diff == 2) {
            int topEle = h1.top();
            h1.pop();
            h2.push(topEle);
            ans.push_back(h1.top());
        }

        else if (diff == -1) {
            int topEle = h2.top();
            h2.pop();
            h1.push(topEle);
            ans.push_back(h1.top());

        }

    }

    return ans;
}
int getProduct(priority_queue<int, vector<int>, greater<int>> pq) {
    int product = 1;
    while (!pq.empty()) {
        product *= pq.top();
        pq.pop();
    }
    return product;
}


vector<int> productOf3(vector<int> A) {
    if (A.size() == 0) {
        return {};
    }

    vector<int> ans(A.size(), -1);
    ans[0] = -1;
    ans[1] = -1;
    int n = A.size();
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(A[0]);
    pq.push(A[1]);
    pq.push(A[2]);
    int res = getProduct(pq);
    ans[2] = (res);

    for (int i = 3; i < n; i++) {
        int currEle = A[i];
        if (currEle > pq.top()) {
            pq.pop();
            pq.push(currEle);
        }
        int res1 = getProduct(pq);
        ans[i] = (res1);
    }
    for (auto num : ans) {
        cout << num << endl;
    }
    return ans;
}

int kthSmallest(vector<vector<int> >& A, int B) {
    int n = A.size();
    vector< pair<int, pair<int, int>> >  v;

    for (int i = 0; i < n; i++) {
        v.push_back(make_pair(A[i][0], make_pair(i, 0)));
    }


    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq(v.begin(), v.end());
    int m = A[0].size();
    int ans;
    while (B--) {
        pair<int, pair<int, int>> element = pq.top();
        pq.pop();
        ans = element.first;
        int row = element.second.first;
        int col = element.second.second;
        cout << "popped element is " << ans << "r " << row << "c " << col << endl;

        // move the column
        if (col + 1 < m) {
            pq.push(make_pair(A[row][col + 1], make_pair(row, col + 1)));
        }
    }

    return ans;
}

int Choose(int N, int n, vector<vector<int>>& memo) {
    if (n == 0 || n == N) return 1;
    if (memo[N][n] != -1) return memo[N][n];

    memo[N][n] = Choose(N - 1, n - 1, memo) + Choose(N - 1, n, memo);
    return memo[N][n];
}

int ways(int n, vector<int>& dp, vector<vector<int>>& memo) {
    if (n == 0) {
        dp[n] = 0;
        return dp[n];
    }

    if (n == 1 || n == 2) {
        dp[n] = 1;
        return dp[n];
    }

    if (dp[n] != -1) return dp[n];
    int height = log2(n);
    int x = static_cast<int>(pow(2, height)) - 1;
    int left = (x - 1) / 2 + min(n - x, (x + 1) / 2);
    int right = n - 1 - left;

    return Choose(n - 1, left, memo) * ways(left, dp, memo) * ways(right, dp, memo);
}


int main() {
    // vector<int> r = maxSubsequence(vector<int>{50, -75}, 2);

    // for (auto num : r) {
    //     cout << num << endl;
    // }
    // bool res = checkValidString("(((*)");
    // cout << res << endl;
    // vector<int> arr = { 1,40,2,3 };
    // vector<int> res = nearlySortedArray(arr, 2);
    // for (auto num : res) {
    //     cout << num << "\t";
    // }

    // solve(4, vector<int>{1, 2, 3, 4, 5, 6});
    vector<int> arr = { 1,2,3,4,5 };
    // vector<int> res = Median(arr);
    // for (auto num : res) {
    //     cout << num << "\t";
    // }
    // productOf3(arr);
    // vector<vector<int>> vec = { {9,11,15}, {10,15,17} };
    // kthSmallest(vec, 6);
    int n = 20;
    int MOD = static_cast<int>(pow(10, 9)) + 7;
    vector<vector<int>> memo(n, vector<int>(n, -1));
    vector<int> dp(n + 1, -1);
    int ans = ways(n, dp, memo);
    cout << ans;
    return 0;
}