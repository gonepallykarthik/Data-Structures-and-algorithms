#include <bits/stdc++.h>
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

void countNodes(TreeNode* root, int max_value, int& ans) {
    if (!root) {
        return;
    }

    if (root->val > max_value) {
        ans += 1;
        max_value = root->val;
    }

    countNodes(root->left, max_value, ans);
    countNodes(root->right, max_value, ans);
}

bool sameTree(TreeNode* p, TreeNode* q) {
    if (p == NULL && q == NULL) {
        return true;
    }

    if (p == NULL || q == NULL) return false;

    if (p->val != q->val) return false;

    return sameTree(p->left, q->left) && sameTree(p->right, q->right);
}


void heapify(vector<int>& arr, int idx, int end) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < end && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < end && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != idx) {
        swap(arr[largest], arr[idx]);
        heapify(arr, largest, end);
    }
}

void heapSort(vector<int>& arr) {
    if (arr.size() == 0) {
        return;
    }
    int n = arr.size();
    // build max heap out of arr
    int startIdx = (n / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, i, n);
    }

    // swap(arr[0], arr[n - 1]);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, 0, i);
    }
}

vector<int> topKFrequent(vector<int>& nums, int k) {
    if (nums.size() == 0) {
        return {};
    }

    priority_queue<pair<int, int>> pq;
    map<int, int> mp;
    for (auto num : nums) {
        mp[num] += 1;
    }

    for (auto it = mp.begin(); it != mp.end(); it++) {
        int value = it->first;
        int cnt = it->second;
        pq.push(make_pair(cnt, value));
    }
    vector<int> res;
    while (k--) {
        pair<int, int> pair = pq.top();
        res.push_back(pair.second);
        pq.pop();
    }

    return res;
}

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    if (arr.size() == 0) {
        return {};
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    for (auto num : arr) {
        pq.push(make_pair(abs(num - x), num));
    }

    vector<int> res;
    while (!pq.empty() && k--) {
        pair<int, int> p = pq.top();
        res.push_back(p.second);
        pq.pop();
    }

    sort(res.begin(), res.end());
    return res;

}


int findKthLargestElement(vector<int> nums, int k) {
    if (nums.size() == 0) {
        return 0;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; i++) {
        pq.push(nums[i]);
    }
    int n = nums.size();
    for (int i = k; i < n; i++) {
        if (nums[i] > pq.top()) {
            pq.pop();
            pq.push(nums[i]);
        }
    }

    return pq.top();
}


vector<int> replaceWithRank(vector<int> arr, int n) {
    // Write your code here.
    if (arr.size() == 0) {
        return {};
    }

    vector<int> res;
    map<int, int> mp;
    vector<int> dummy = arr;
    sort(dummy.begin(), dummy.end());

    set<int> s;
    int rank = 1;
    for (int i = 0; i < dummy.size(); i++) {
        int currentNum = dummy[i];
        cout << currentNum << endl;
        if (s.find(currentNum) == s.end()) //
        {
            cout << "exe" << endl;
            mp.insert({ currentNum, rank });
            s.insert(arr[i]);
            rank += 1;
        }
    }

    for (int i = 0; i < n; i++) {
        dummy[i] = mp[arr[i]];
    }


    return dummy;
}


class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq;

    KthLargest(int k, vector<int>& nums) {
        cout << "exe";
        for (int i = 0; i < k; i++) {
            this->pq.push(nums[i]);
        }
        int n = nums.size();
        for (int j = k; j < n; j++) {
            int currentEle = nums[j];
            if (currentEle > pq.top()) {
                this->pq.pop();
                this->pq.push(currentEle);
            }
        }
    }

    int add(int val) {
        if (this->pq.size() == 0) {
            cout << "exe";
            this->pq.push(val);
        }

        else if (val > pq.top()) {
            this->pq.pop();
            this->pq.push(val);
        }

        return pq.top();
    }
};

int leastInterval(vector<char>& tasks, int n) {
    if (tasks.size() == 0) {
        return 0;
    }

    map<char, int> mp;
    for (auto character : tasks) {
        mp[character] += 1;
    }
    priority_queue<int> pq;
    deque< pair<int, int> > q;

    for (auto it : mp) {
        pq.push(it.second);
    }
    int time = 0;
    while (!pq.empty() || !q.empty()) {
        time += 1;
        if (!pq.empty()) {
            int topEle = pq.top();
            pq.pop();
            if (topEle - 1 > 0) {
                q.push_back(make_pair(topEle - 1, time + n));
            }
        }
        pair<int, int> p = q.front();
        if (p.second == time) {
            pq.push(p.first);
            q.pop_front();
        }
    }

    return time;
}

int bulbs(vector<int>& A) {
    if (A.size() == 0) {
        return 0;
    }
    int cost = 0;
    int n = A.size();
    for (int i = 0; i < n; i++) {
        if (cost % 2 == 0) A[i] = A[i];
        else A[i] = !A[i];

        if (A[i] % 2 == 1) continue;
        else cost += 1;
    }

    return cost;
}

int candy(vector<int>& A) {
    if (A.size() == 0) {
        return 0;
    }

    vector<int> candies(A.size(), 1);
    int n = A.size();
    for (int i = 1; i < n; i++) {
        if (A[i] > A[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        if (A[i] > A[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    int sum = 0;
    for (auto num : candies) sum += num;

    return sum;
}

bool validPalindrome(string s) {
    if (s.size() == 0) {
        return true;
    }
    int n = s.size();
    bool delete_char = false;
    if (s[0] != s[n - 1]) return false;
    int start = 1;
    int end = n - 2;
    while (start <= end) {
        if (s[start] != s[end]) {
            if (delete_char == true) return false;
            else {
                delete_char = true;
            }
        }
        start += 1;
        end -= 1;
    }

    return true;
}





int main() {

    // vector<int> arr = { 1,2,3,4,5 };
    // heapSort(arr);int n = arr.size();
    // Index of last non-leaf node
    // int startIdx = (n / 2) - 1;
    // Perform reverse level order traversal
    // from last non-leaf node and heapify each node
    // for (int i = startIdx; i >= 0; i--) {
        // heapify(arr, n, i);
    // }

    // for (auto num : arr) {
    //     cout << num << "\t";
    // }

    // vector<int> nums = { 1,2,3,4,5 };
    // findClosestElements(arr, 4, 3);
    // replaceWithRank(vector<int>{1, 2, 6, 9, 2}, 5);


    //Your KthLargest object will be instantiated and called as such :
    vector<int> nums = {};
    // KthLargest* obj = new KthLargest(1, nums);
    // int param_1 = obj->add(-3);
    // cout << param_1;
    // vector<char> tasks = { 'A','A','A','B','B','B' };
    // int  n = 2;
    // int time = leastInterval(tasks, n);
    // cout << time << "t" << endl;

    bool isvalid = validPalindrome("abc");
    cout << isvalid;
    return 0;
}