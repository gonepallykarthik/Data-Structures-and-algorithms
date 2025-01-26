#include <bits/stdc++.h>
using namespace std;

// this is Node -> contains key, value
template <typename KeyType, typename ValueType>
class HMNode {
private:
    KeyType key;
    ValueType value;
public:
    HMNode(KeyType k, ValueType v) {
        key = k;
        value = v;
    }

    pair<KeyType, ValueType> getKey() {
        return make_pair(key, value);
    }
};

template <typename KeyType, typename ValueType>
class Hmap {
public:
    int size;
    int bucketSize = 10;
    vector<vector<HMNode<KeyType, ValueType>>> mp;

    Hmap() {
        initBucket();
        size = 0;
    }

private:
    void initBucket() {
        vector<vector<HMNode<KeyType, ValueType>>>mp(bucketSize, vector<int>(bucketSize, -1));
    }
};

int nchoc(int A, vector<int> B) {
    long long ans = 0;
    int MOD = (int)pow(10, 9) + 7;
    priority_queue<int> pq;

    for (auto num : B) {
        pq.push(num);
    }

    while (A > 0) {
        int topEle = pq.top();
        pq.pop();
        cout << "top ele is " << topEle << endl;
        ans += topEle;

        pq.push(floor(topEle / 2));
        A -= 1;
    }

    return ans % MOD;
}

int minRope(vector<int> A) {
    if (A.size() == 0) {
        return 0;
    }

    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto num : A) {
        pq.push(num);
    }

    while (pq.size() > 1) {
        int t1 = pq.top();
        pq.pop();
        int t2 = pq.top();
        pq.pop();

        ans += t1 + t2;
        pq.push((t1 + t2));
    }

    return ans;
}


//  Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};


// ListNode* mergeKLists(vector<ListNode*>& A) {
//     // Do not write main() function.
//     // Do not read input, instead use the arguments to the function.
//     // Do not print the output, instead return values as specified
//     // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
//     if (A.size() == 0) {
//         return nullptr;
//     }

//     int n = A.size();
//     ListNode* curr = merge(A[0], A[1]);

//     int i = 2;
//     while (i < n) {
//         ListNode* temp = merge(curr, A[i]);
//         curr = temp;
//         i += 1;
//     }

//     return curr;

// }

ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode* res = new ListNode(-1);
    ListNode* temp = res;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            temp->next = l1;
            l1 = l1->next;
        }
        else {
            temp->next = l2;
            l2 = l2->next;
        }

        temp = temp->next;
    }

    if (l1 == NULL) {
        temp->next = l2;
    }
    else {
        temp->next = l1;
    }

    return res->next;
}

int candies(vector<int> A, int B) {
    if (A.size() == 1) {
        cout << A[0] / 2;
        return A[0] / 2;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    int n = A.size();
    for (int i = 0; i < n; i++) {
        pq.push(A[i]);
    }
    int ans = 0;
    while (pq.size() > 1) {
        int topEle = pq.top();
        pq.pop();
        if (topEle > B) {
            continue;
        }
        cout << topEle << "top ele " << endl;
        ans += topEle / 2;
        cout << "ans is " << ans << endl;
        int min_ele = pq.top();
        cout << min_ele << "min_ele is poped" << endl;
        pq.pop();
        pq.push(min_ele + (topEle / 2));
    }

    int topEle = pq.top();
    if (topEle > B) {
        return ans;
    }
    else {
        ans += topEle / 2;
    }
    cout << ans;
}

long long pickGifts(vector<int> gifts, int k) {
    long long res = 0;
    if (gifts.size() == 0) {
        return res;
    }
    int n = gifts.size();
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.push(gifts[i]);
    }


    while (k > 0) {
        int topEle = pq.top();
        pq.pop();
        int pushedEle = (static_cast<int>(sqrt(topEle)));
        cout << "pushed ele is " << pushedEle << endl;
        pq.push(pushedEle);
        k -= 1;
    }

    while (!pq.empty()) {
        res += pq.top();
        cout << pq.top() << "\t";
        pq.pop();
    }

    return res;
}

int kthSmallest(int arr[], int l, int r, int k) {
    //code here
    cout << "exe";
    if (l >= r) {
        return 0;
    }
    priority_queue<int> pq;

    for (int i = l; i < k; i++) {
        pq.push(arr[i]);
    }

    for (int j = k; j <= r; j++) {
        int currentEle = arr[j];
        int topEle = pq.top();
        if (currentEle < topEle) {
            pq.pop();
            pq.push(currentEle);
        }
    }

    // while (!pq.empty()) {
    //     cout << pq.top() << "\t";
    //     pq.pop();
    // }
    return pq.top();
}

long long sumBetweenTwoKth(long long A[], long long N, long long K1, long long K2)
{
    // Your code goes here
    priority_queue<int> pq;
    priority_queue<int> pq2;
    K2 = K2 - 1;
    for (int i = 0; i < K1; i++) {
        pq.push(A[i]);
    }

    for (int i = 0; i < K2; i++) {
        pq2.push(A[i]);
    }

    for (int i = K1; i < N; i++) {
        int topEle = pq.top();
        int currentEle = A[i];
        if (currentEle < topEle) {
            pq.pop();
            pq.push(currentEle);
        }
    }

    for (int j = K2; j < N; j++) {
        int topEle = pq2.top();
        int currrentEle = A[j];
        if (currrentEle < topEle) {
            pq2.pop();
            pq2.push(currrentEle);
        }
    }

    int long long res = 0;
    long long sum1 = 0;
    while (!pq.empty()) {
        sum1 += pq.top();
        pq.pop();
    }
    long long sum2 = 0;
    while (!pq2.empty()) {
        sum2 += pq2.top();
        pq2.pop();
    }

    cout << sum1 << endl;
    cout << sum2 << endl;
    cout << sum2 - sum1;
    return res;
}



int main() {
    // cout << "welcome to this application";
    HMNode<int, int> mp(1, 2);
    pair<int, int> res = mp.getKey();
    // cout << res.second;
    // cout << nchoc(10, vector<int>{ 2147483647, 2000000014, 2147483647});
    // int ans = candies(vector<int>{355, 667}, 867);
    // cout << ans;
    // int ans = static_cast<int>(sqrt(10));
    // cout << ans;
    // long long res2 = pickGifts(vector<int>{25, 64, 9, 4, 100}, 4);
    // cout << res2;
    // int arr[] = { 7, 10, 4, 3, 20, 15 };
    // int ans = kthSmallest(arr, 0, 5, 3);
    // cout << ans;
    long long arr[] = { 20,8,22,4,12,10,14 };
    sumBetweenTwoKth(arr, 7, 3, 6);
    return 0;
}