#include <bits/stdc++.h>
using namespace std;


int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    if (grid[n - 1][m - 1] == 1) {
        return 0;
    }

    vector<vector<int>> dp(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 0) {
            if (i > 0 && dp[i - 1][0] == 0) {
                dp[i][0] = 0;
            }
            else {
                dp[i][0] = 1;
            }
        }
        else if (grid[i][0] == 1) {
            dp[i][0] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        if (grid[0][i] == 0) {
            if (i > 0 && dp[0][i - 1] == 0) {
                dp[0][i] = 0;
            }
            else {
                dp[0][i] = 1;
            }
        }
        else if (grid[0][i] == 1) {
            dp[0][i] = 0;
        }
    }

    for (auto row : dp) {
        for (auto num : row) {
            cout << num << "\t";
        }
        cout << endl;
    }

    for (int row = 1; row < n; row++) {
        for (int col = 1; col < m; col++) {
            if (grid[row][col] == 1) {
                dp[row][col] = 0;
            }
            else {
                dp[row][col] = dp[row][col - 1] + dp[row - 1][col];
            }
        }
    }

    return dp[n - 1][m - 1];
}

int minimumPathSuminTriangle(int row, int col, vector<vector<int>>& triangle) {
    if (row == 0) {
        return triangle[0][0];
    }

    if (row < 0 || col < 0 || col >= triangle[row].size()) {
        return INT_MAX;
    }

    int up = INT_MAX;
    int subProblem2 = minimumPathSuminTriangle(row - 1, col, triangle);
    if (subProblem2 != INT_MAX) {
        up = triangle[row][col] + subProblem2;
    }

    int left = INT_MAX;
    int subProblem = minimumPathSuminTriangle(row - 1, col - 1, triangle);
    if (subProblem != INT_MAX) {
        left = triangle[row][col] + subProblem;
    }
    // cout << "row and col is " << row << col << "\t" << up << left << endl;
    return min(up, left);
}


int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.size() == 0) {
        return 0;
    }
    int n = triangle.size();
    int ans = INT_MAX;
    for (int i = 0; i < triangle[n - 1].size(); i++) {
        ans = min(ans, minimumPathSuminTriangle(n - 1, i, triangle));
    }
    cout << ans;
    return ans;

}

int firstMissingPositive(vector<int>& nums) {
    if (nums.size() == 0) {
        return 1;
    }
    int ans = nums.size();
    int i = 0;
    int n = nums.size();
    while (i < n) {
        if (nums[i] <= 0) {
            i += 1;
            continue;
        }

        else if (nums[i] >= 1 && nums[i] <= n) {
            if (i == nums[i] - 1) {
                i += 1;
            }
            else {
                int newIdx = nums[i] - 1;
                if (nums[newIdx] == nums[i]) {
                    i += 1;
                    continue;
                }
                swap(nums[i], nums[newIdx]);
            }
        }
        else {
            i += 1;
        }
    }


    for (int i = 0; i < n; i++) {
        if (i != nums[i] - 1) {
            return i + 1;
        }
    }

    return ans + 1;
}

vector<int> subarraySum(vector<int>arr, int n, long long s)
{
    // Your code here
    if (arr.size() == 0) {
        return { -1,-1 };
    }

    vector<int> ans(2, 1e9);
    long long currentSum = 0;
    int leftIdx = 0;

    for (int right = 0; right < n; right++) {
        currentSum += arr[right];
        cout << currentSum << endl;
        while (leftIdx <= right && currentSum > s)
        {
            if (currentSum == s) {
                cout << "this block" << "\t" << currentSum << endl;
                if (leftIdx < ans[0]) {
                    // update
                    ans[0] = leftIdx + 1;
                    ans[1] = right + 1;
                }
            }

            currentSum -= arr[leftIdx];
            // cout << "after " << currentSum << endl;
            leftIdx += 1;
        }

    }
    if (ans[0] == 1e9 || ans[1] == 1e9) {
        return { -1,-1 };
    }

    cout << ans[0] << ans[1];
    return ans;
}

int peakElement(vector<int> arr, int n)
{
    // Your code here
    if (n == 1) {
        return arr[0];
    }

    if (arr[0] >= arr[1]) {
        return 0;
    }

    if (arr[n - 1] >= arr[n - 2]) {
        return n - 1;
    }

    for (int i = 1; i < n - 1; i++) {
        if (arr[i] >= arr[i + 1] && arr[i] >= arr[i - 1]) {
            return i;
        }
    }

    return -1;
}

int maxProduct(vector<int>& nums) {
    int ans = -1e9;
    int prefix = 1;
    for (auto num : nums) {
        prefix *= num;
        ans = max(ans, prefix);
        if (prefix == 0) {
            prefix = 1;
        }
    }

    int n = nums.size() - 1;
    int suff = 1;
    for (int i = n - 1; i >= 0; i--) {
        suff *= nums[i];
        cout << suff << endl;
        ans = max(ans, suff);
        if (suff == 0) {
            suff = 1;
        }
    }

    return ans;
}
int longestOnes(vector<int>& nums, int k) {
    if (nums.size() == 0) {
        return 0;
    }
    int ans = -1e9;
    int left = 0;
    int a = k;
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) a -= 1;
        while (left <= right && a < 0) {
            if (nums[left] == 0) {
                a = a + 1;
            }
            left += 1;
        }
        ans = max(ans, right - left + 1);
    }
    cout << ans;
    return ans;
}

int totalFruits(int N, vector<int>& fruits) {
    if (fruits.size() == 0) {
        return 0;
    }
    map<int, int> mp;
    int ans = -1e9;
    int left = 0;
    for (int right = 0; right < N; right++) {
        mp[fruits[right]] += 1;
        while (left <= right && mp.size() > 2) {
            mp[fruits[left]] -= 1;
            if (mp[fruits[left]] == 0) {
                mp.erase(fruits[left]);
            }
            left += 1;
        }
        ans = max(ans, right - left + 1);
    }
    cout << ans;
    return ans;

}

int search(vector<int>& nums, int target) {
    int n = nums.size();
    int left = 0;
    int right = n - 1;
    while (left <= right)
    {
        /* code */
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target) {
            if (nums[left] <= target && target <= nums[mid]) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        else {
            if (nums[mid] <= target && target <= nums[right]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int findPeakElement(vector<int>& nums) {
    if (nums.size() == 1) {
        return 0;
    }
    int n = nums.size();
    int left = 1;
    int right = n - 2;

    if (nums[0] > nums[1]) {
        return 0;
    }

    if (nums[n - 1] > nums[n - 2]) {
        return n - 1;
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
            return mid;
        }

        // find out whether it is increasing or decreasing
        // it is increasing
        else if (nums[mid] > nums[mid - 1]) {
            left = mid + 1;
        }

        // if it is decreasing 
        else {
            right = mid - 1;
        }
    }

    return n - 1;
}
int isValid(vector<int>& bloomDay, int day, int& m, int& k) {
    int n = bloomDay.size(); //size of the array
    int cnt = 0;
    int noOfB = 0;
    // count the number of bouquets:
    for (int i = 0; i < n; i++) {
        if (bloomDay[i] <= day) {
            cnt++;
        }
        else {
            noOfB += (cnt / k);
            cnt = 0;
        }
    }
    noOfB += (cnt / k);
    return noOfB >= m;
}

int minDays(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size();
    if (m * k > n) {
        return -1;
    }
    int min_num = 1e9;
    int max_num = -1e9;
    for (auto num : bloomDay) {
        min_num = min(min_num, num);
        max_num = max(max_num, num);
    }
    int ans = 1e9;
    int left = min_num;
    int right = max_num;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (isValid(bloomDay, mid, m, k) == 1) {

            ans = mid;
            right = mid - 1;
        }
        else {

            left = mid + 1;
        }
    }

    return ans == 1e9 ? -1 : ans;
}

int calculateDays(vector<int>& weights, int cap) {
    int days = 1;
    int load = 0;
    for (int i = 0; i < weights.size(); i++) {
        if (load + weights[i] > cap) {
            days += 1;
            load = weights[i];
        }
        else {
            load += weights[i];
        }
    }
    return days;
}

int shipWithinDays(vector<int>& weights, int days) {
    int n = weights.size();
    int total_weight = 0;
    for (auto num : weights) {
        total_weight += num;
    }
    int left = 1;
    int ans = 1e9;
    int right = total_weight;
    while (left <= right) {
        int mid = (left + right) / 2;
        int total_days = calculateDays(weights, mid);
        cout << total_days << endl;
        if (total_days <= days) {
            ans = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return ans;
}

int calculate(vector<int>& boards, int cap) {
    int cnt = 1;
    int load = 0;
    for (int i = 0; i < boards.size(); i++) {
        if (load + boards[i] > cap) {
            cnt += 1;
            load = boards[i];
        }
        else {
            load += boards[i];
        }
    }
    return cnt;
}

int findLargestMinDistance(vector<int>& boards, int k) {
    int n = boards.size();
    int ans = 1e9;
    int left = *max_element(boards.begin(), boards.end());
    int right = accumulate(boards.begin(), boards.end(), 0);
    while (left <= right) {
        int mid = (left + right) / 2;
        int total_men = calculate(boards, mid);
        if (total_men > k) {
            left = mid + 1;
        }
        else {
            ans = mid;
            right = mid - 1;
        }
    }
    return ans;
}

class CustomComparator {
public:
    bool operator()(const vector<int> a, const vector<int> b) {
        int r1 = sqrt(pow((a[0] - 0), 2) + pow((a[1] - 0), 2));
        int r2 = sqrt(pow((b[0] - 0), 2) + pow((b[1] - 0), 2));
        return r1 < r2;
    }
};

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    if (points.size() == 0) {
        return {};
    }
    vector<vector<int>> res;
    sort(points.begin(), points.end(), CustomComparator());
    int i = 0;
    while (k--) {
        res.push_back(points[i]);
        i += 1;
    }
    for (auto r : res) {
        for (auto num : r) {
            cout << num << "\t";
        }
        cout << endl;
    }
    return res;
}

int maxLen(vector<int>& A, int n)
{
    // Your code here
    map<int, int> mp;
    int ans = -1e9;
    mp.insert({ 0, -1 });
    int currentSum = 0;
    for (int i = 0; i < n; i++) {
        currentSum += A[i];
        if (mp.find(currentSum) != mp.end()) {
            int idx = mp[currentSum] + 1;
            ans = max(ans, i - idx + 1);
        }
        else {
            mp[currentSum] = i;
        }
    }
    return ans;
}

bool countCows(vector<int>& stalls, int distance, int k) {
    int coord = stalls[0];
    int cnt = 1;
    for (int i = 1; i < stalls.size(); i++) {
        if (abs(stalls[i] - coord) >= distance) {
            cnt += 1;
            coord = stalls[i];
        }

        if (cnt == k) {
            return true;
        }
    }

    return false;
}

int solve(int n, int k, vector<int>& stalls) {

    // Write your code here
    sort(stalls.begin(), stalls.end());
    int left = stalls[0];
    int ans = 1e9;
    int right = stalls[n - 1] - stalls[0];
    while (left <= right) {
        int mid = (left + right) / 2;

        if (countCows(stalls, mid, k) == true) {
            ans = mid;
            left = mid + 1;
        }

        else {
            right = mid - 1;
        }
    }

    return ans;
}

vector<int> prevSmaller(vector<int>& A) {
    stack<int> st;
    vector<int> res(A.size(), -1);
    st.push(A[0]);

    for (int i = 1; i < A.size(); i++) {
        int current = A[i];
        if (current > st.top()) {
            res[i] = st.top();
            st.push(current);
        }

        else {
            while (!st.empty() && current <= st.top()) {
                st.pop();
            }

            res[i] = st.empty() ? -1 : st.top();
            st.push(current);
        }
    }
    for (auto num : res) {
        cout << num << "\t";
    }

    return res;
}

vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;
    vector<int> res;
    int n = asteroids.size();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && asteroids[i] < 0 && st.top() > 0) {
            int r = asteroids[i] + st.top();
            if (r == 0) {
                cout << "this exe";
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
        res.insert(res.begin(), st.top());
        st.pop();
    }
    return res;
}

int main() {
    vector<vector<int>> grid = {
        {0,1,0,0,0},
        { 1,0,0,0,0 },
        { 0,0,0,0,0 },
        { 0,0,0,0,0 }
    };
    // uniquePathsWithObstacles(grid);
    vector<vector<int>> triangle = {
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3}
    };
    // minimumTotal(triangle);
    // cout << INT_MAX + 1;
    // vector<int> nums = { 0 };
    // cout << firstMissingPositive(nums);
    // long long sum = 0;
    // subarraySum(nums, nums.size(), sum);
    // vector<int> nums = { 1, -1, 3, 2, -7, -5, 11, 6 };
    // cout << peakElement(nums, nums.size());
    // segregateElements(nums, nums.size());
    // for (auto num : nums) {
    //     cout << num << "\t";
    // }
    // vector<int> nums1 = { 3,-1,4 };
    // maxProduct(nums1);
    // vector<int> nums = { 0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1 };
    // int k = 3;
    // longestOnes(nums, k);
    // vector<int> fruits = { 0, 1, 2, 2, 2, 2 };
    // cout << totalFruits(fruits.size(), fruits);
    // vector<int> nums = { 1,2,3,1 };
    // findPeakElement(nums);
    // vector<int> nums = { 3,2,2,4,1,4 };
    // int m = 2;
    // int k = 3;
    // cout << shipWithinDays(nums, 3);
    // cout << isValid(nums, 8, m, k);
    // cout << minDays(nums, m, k);
    // int N = 4;
    // vector<int> boards = { 10, 20, 30, 40 };
    // int  k = 2;
    // cout << findLargestMinDistance(boards, k);
    vector<vector<int>> points = {
        {1,3},
        {-2,2}
    };
    // kClosest(points, 1);
    vector<int> nums = { 1 };
    // cout << maxLen(nums, nums.size());
    // cout << solve(nums.size(), 3, nums);
    // prevSmaller(nums);
    vector<int> aes = { 8,-8 };
    asteroidCollision(aes);
    return 0;

}