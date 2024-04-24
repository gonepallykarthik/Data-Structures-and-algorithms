#include <bits/stdc++.h>
using namespace std;

class CustomComparator {
public:
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    }
};


int MaximumProfit(vector<int> A, vector<int> B) {
    int n = A.size();
    vector<pair<int, int>> Items;
    int MOD = static_cast<int>(pow(10, 9)) + 7;
    for (int i = 0; i < n; i++) {
        pair<int, int> p = { A[i], B[i] };
        Items.push_back(p);
    }

    sort(Items.begin(), Items.end(), CustomComparator());
    int time = 0;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (auto pair : Items) {
        int profit = pair.second;
        int expiresTime = pair.first;
        // cout << "profit" << profit << "expTime" << expiresTime << endl;
        if (time < expiresTime) {
            pq.push(profit);
            cout << "top Element is" << pq.top() << endl;
            time += 1;
        }
        else
        {
            if (pq.top() >= profit) continue;
            else {
                pq.pop();
                pq.push(profit);
            }
        }
    }

    int total_profit = 0;
    while (!pq.empty()) {
        total_profit += pq.top();
        pq.pop();
    }


    return total_profit;
}


class SortEndTime {
public:
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    }
};


int FinishMaximumJobs(vector<int> A, vector<int> B) {
    int n = A.size();
    vector<pair<int, int>> Items;
    int MOD = static_cast<int>(pow(10, 9)) + 7;
    for (int i = 0; i < n; i++) {
        pair<int, int> p = { A[i], B[i] };
        Items.push_back(p);
    }

    sort(Items.begin(), Items.end(), SortEndTime());
    int jobs = 1;
    int prev_start = Items[0].first;
    int prev_end = Items[0].second;

    for (auto pair : Items) {
        int currentStart = pair.first;
        int currentEnd = pair.second;
        if (prev_end <= currentStart) {
            prev_start = currentStart;
            prev_end = currentEnd;
            jobs += 1;
        }
    }

    return jobs;

}

int mice(vector<int>& A, vector<int>& B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int time = INT_MIN;
    int n = A.size();
    for (int i = 0; i < n; i++) {
        time = max(time, abs(A[i] - B[i]));
    }

    return time;
}

void coinChangeProblem() {
    int A = 2011;
    int result = static_cast<int>(log(A) / log(5));
    double limit = pow(5, result);
    vector<int> coins;
    int idx = 1;
    cout << "limit" << limit << endl;
    while (idx <= (int)limit) {
        coins.push_back(idx);
        idx *= 5;
    }
    for (auto num : coins) cout << num << "\t";
    int n = coins.size();
    int total_denom = A;
    int indx = n - 1;
    int total_coins = 0;
    while (total_denom > 0 && indx >= 0) {
        if (total_denom >= coins[indx]) {
            int required = total_denom / coins[indx];
            int remainder = total_denom % coins[indx];
            cout << "r is " << required << endl << "coins taken is " << coins[indx] << "indx is " << indx;
            total_coins += required;
            total_denom = remainder;
            cout << "rem is " << remainder << endl;
        }
        else {
            cout << "this executed" << endl;
            indx -= 1;
        }
    }
    cout << "t is " << total_coins;
}

vector<vector<int>> taskAssignment(int k, vector<int> tasks) {
    // Write your code here.
    if (tasks.size() == 0) {
        return {};
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min;
    priority_queue<pair<int, int>> max;
    int n = tasks.size();
    for (int i = 0; i < n; i++) {
        min.push({ tasks[i], i });
        max.push({ tasks[i], i });
    }
    vector<vector<int>> res;
    while (k--) {
        pair<int, int> topMax = max.top();
        max.pop();
        pair<int, int> topMin = min.top();
        min.pop();
        res.push_back({ topMin.second, topMax.second });
    }

    return res;
}






int main() {

    // int r = MaximumProfit(vector<int>{1, 3, 2, 3, 3}, vector<int>{5, 6, 1, 3, 9});
    // cout << r;
    // int r = FinishMaximumJobs(vector<int>{3, 2, 6}, vector<int>{9, 8, 9});
    // cout << r;
    vector<int> tasks = { 1,3,5,3,1,4 };
    vector<vector<int>> res = taskAssignment(3, tasks);
    for (auto row : res) {
        for (auto col : row) {
            cout << col << "\t";
        }
        cout << endl;
    }
    return 0;
}