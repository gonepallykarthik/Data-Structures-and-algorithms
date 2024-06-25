#include <bits/stdc++.h>
using namespace std;

int checkTowers(int idx, vector<int>& A, int start) {
    int seen_towers = 0;
    int prev_max = start;
    for (int i = idx; i < A.size(); i++) {
        if (A[i] >= start && A[i] >= prev_max) {
            seen_towers += 1;
        }
        prev_max = max(prev_max, A[i]);
    }

    return seen_towers;
}


int solve(vector<int>& A) {
    int max_tower_seen = -1e9;
    int idx = 1e9;

    for (int i = 0; i < A.size(); i++) {
        int seen_towers = checkTowers(i + 1, A, A[i]);
        cout << "s is " << seen_towers << endl;


        if (seen_towers >= max_tower_seen) {
            if (seen_towers == max_tower_seen) {
                if (i < idx) {
                    idx = i;
                }
            }
            else {
                max_tower_seen = seen_towers;
                idx = i;
            }
        }
    }

    return idx + 1;
}

bool checkIfPangram(string sentence) {
    vector<int> vec(26, 0);

    for (auto character : sentence) {
        vec[character - 97] += 1;
    }

    for (int i = 0; i < 26; i++) {
        if (vec[i] == 0) return false;
    }

    return true;
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    if (nums.size() == 0) {
        return{};
    }
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    int n = nums.size();
    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            int start = j + 1;
            int end = nums.size() - 1;
            while (start < end) {
                long long currentSum = nums[i] + nums[j] + nums[start] + nums[end];

                if (currentSum == target) {
                    vector<int> temp = { nums[i], nums[j], nums[start], nums[end] };
                    ans.push_back(temp);
                    start += 1;
                    end -= 1;
                }

                else if (currentSum > target) {
                    end -= 1;
                }
                else {
                    start += 1;
                }

            }
        }
    }
    return ans;
}

int getDifficulty(vector<pair<int, int>>& dp, int maxWork) {
    int maxProfit = INT_MIN;
    for (int i = 0; i < dp.size(); i++) {
        if (dp[i].first <= maxWork) {
            if (dp[i].second > maxProfit) {
                maxProfit = dp[i].second;
            }
        }
    }

    return maxProfit == INT_MIN ? 0 : maxProfit;
}

int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    int ans = 0;
    vector<pair<int, int>> dp;
    for (int i = 0; i < difficulty.size(); i++) {
        dp.push_back(make_pair(difficulty[i], profit[i]));
    }
    sort(dp.begin(), dp.end(), [](const auto& first, const auto& second) {
        return first.second > second.second;
        });

    for (int i = 0; i < worker.size(); i++) {
        ans += getDifficulty(dp, worker[i]);
    }

    return ans;
}

vector<int> asteroidCollision(vector<int>& asteroids) {
    if (asteroids.size() == 0) {
        return {};
    }
    stack<int> st;
    int n = asteroids.size();
    for (int i = 0; i < n; i++) {

        while (!st.empty() && asteroids[i] < 0 && st.top() > 0) {
            // three cases 
            int r = asteroids[i] + st.top();
            if (r == 0) {
                asteroids[i] = 0;
                st.pop();
            }
            else if (r > 0) {
                asteroids[i] = 0;
            }
            else if (r < 0) {
                st.pop();
            }

        }

        if (asteroids[i] != 0) {
            st.push(asteroids[i]);
        }
    }

    while (!st.empty()) {
        cout << st.top() << "\t";
        st.pop();
    }
    return {};
}

int camelcase(string s) {
    if (s.size() == 0) {
        return 0;
    }

    int ans = 1;
    for (int i = 1; i < s.size(); i++) {
        int val = static_cast<int>(s[i]);
        if (val < 97 || val > 122) {
            ans += 1;
        }
    }

    return ans;
}

long candies(int n, vector<int> arr) {
    if (arr.size() == 0) {
        return 0;
    }
    vector<int> nums(arr.size(), -1);
    nums[0] = 1;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > arr[i - 1]) {
            nums[i] = nums[i - 1] + 1;
        }
        else {
            nums[i] = 1;
        }
    }
    int s = arr.size();
    for (int i = s - 2; i >= 0; i--) {
        if (arr[i] > arr[i + 1]) {
            if (nums[i] > nums[i + 1]) continue;
            else {
                nums[i] = nums[i + 1] + 1;
            }
        }
    }
    long res = 0;
    for (auto num : nums) {
        res += num;
    }
    return res;
}



// int getLevelDiff(Node* root)
// {
//     //Your code here
//     if (root == NULL) return 0;
//     int odd_sum = 0;
//     int even_sum = 0;
//     queue<pair<int, int>> q;
//     q.push(make_pair(root, 1));

//     while (!q.empty()) {
//         int level = q.front().second;
//         Node* node = q.front().first;
//         q.pop();
//         if (level % 2 == 0) {
//             even_sum += node->data;
//         }
//         else {
//             odd_sum += node->data;
//         }

//         if (node->left != NULL) {
//             q.push(make_pair(node->left, level + 1));
//         }

//         if (node->right != NULL) {
//             q.push(make_pair(node->right, level + 1));
//         }
//     }
// }

vector<int> getMinandMax(int start, int end, vector<int>& nums) {
    int max_v = -1e9;
    int min_v = 1e9;

    for (int i = start; i <= end; i++) {
        max_v = max(max_v, nums[i]);
        min_v = min(min_v, nums[i]);
    }
    cout << max_v << min_v << endl;
    return { max_v, min_v };
}


int longestSubarray(vector<int>& nums, int limit) {
    if (nums.size() == 0) {
        return 0;
    }
    deque<int> max_queue;
    deque<int> min_queue;
    int left = 0;
    int ans = -1e9;
    for (int right = 0; right < nums.size(); right++) {

        while (!max_queue.empty() && nums[right] > max_queue.back()) {
            max_queue.pop_back();
        }
        max_queue.push_back(nums[right]);

        while (!min_queue.empty() && nums[right] < min_queue.back()) {
            min_queue.pop_back();
        }

        min_queue.push_back(nums[right]);

        while (left <= right && !max_queue.empty() && !min_queue.empty() && abs(max_queue.front() - min_queue.front()) > limit) {
            if (nums[left] == max_queue.front()) {
                max_queue.pop_front();
            }

            if (nums[left] == min_queue.front()) {
                min_queue.pop_front();
            }
            left += 1;
        }

        if (abs(max_queue.front() - min_queue.front()) <= limit) {
            ans = max(ans, (right - left + 1));
        }
    }
    return ans;
}

string countAndSay(int n) {
    if (n == 1) {
        return "1";
    }

    if (n == 2) {
        return "11";
    }

    string say = countAndSay(n - 1);
    // process the string 
    string res = "";
    int len = say.size();
    int cnt = 1;
    char curr = say[0];
    for (int i = 1; i < len; i++) {
        if (say[i] == say[i - 1]) {
            cnt += 1;
        }
        else {
            res += to_string(cnt);
            res += curr;
            cnt = 1;
            curr = say[i];
        }
    }
    res += to_string(cnt);
    res += curr;
    return res;
}

int main() {
    // vector<int> b = { 2,24,17,10,16,19,22 };
    // cout << solve(b);
    // cout << checkIfPangram("thequickbrownfoxjumpsoverthelazydog");
    // vector<int> nums = { 1,0,-1,0,-2,2 };
    // fourSum(nums, 0);
    // vector<int> diff = { 68,35,52,47,86 };
    // vector<int> profit = { 67,17,1,81,3 };
    // vector<int> worker = { 92,10,85,84,82 };
    // maxProfitAssignment(diff, profit, worker);
    // vector<int> asteroids = { 5,10,-5 };
    // asteroidCollision(asteroids);
    // cout << camelcase("saveChangesInTheEditor");
    // cout << camelcase("abcde");
    // int number = 3;
    // int count = 0;
    // while (number) {
    //     count += number & 1;
    //     number >>= 1;
    // }
    // cout << count;
    // vector<int> arr = { 1,2,2 };
    // candies(arr.size(), arr);
    // vector<int> nums = { 4,2,2,2,4,4,2,2 };
    // int limit = 0;
    // cout << longestSubarray(nums, limit);
    cout << countAndSay(4);
    return 0;
}