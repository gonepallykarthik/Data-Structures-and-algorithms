#include <bits/stdc++.h>
using namespace std;

string decodeString(string s) {
    if (s.size() == 0) {
        return "";
    }
    stack<char> st;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ']') {
            string curr = "";
            while (st.top() != '[') {
                curr = st.top() + curr;
                st.pop();
            }

            // pop for '['
            st.pop();
            // get the number
            string number = "";
            while (!st.empty() && isdigit(st.top())) {
                number = st.top() + number;
                st.pop();
            }

            int time = stoi(number);
            while (time--) {
                for (int k = 0; k < curr.size(); k++) {
                    st.push(curr[k]);
                }
            }
        }

        else {
            st.push(s[i]);
        }
    }
    string result = "";
    while (!st.empty()) {
        result = st.top() + result;
        st.pop();
    }

    return result;
}

int romanToInt(string s) {
    if (s.size() == 0) {
        return 0;
    }
    map<char, int> mp;
    mp.insert({ 'I', 1 });
    mp.insert({ 'V', 5 });
    // mp.insert({ 'IV', 4 });
    mp.insert({ 'X', 10 });
    // mp.insert({ 'IX', 9 });
    mp.insert({ 'L', 50 });
    mp.insert({ 'C', 100 });
    mp.insert({ 'D', 500 });
    mp.insert({ 'M', 1000 });
    // mp.insert({ 'XL', 40 });
    // mp.insert({ 'XC', 90 });
    // mp.insert({ 'CD', 400 });
    // mp.insert({ 'CM', 900 });
    int res = 0;
    int i = 0;
    while (i < s.size()) {
        char curr = s[i];
        // TODO validate 6 conditons
        if (curr == 'I' && s[i + 1] == 'V') {
            res += 4;
            i += 2;
        }
        else if (curr == 'I' && s[i + 1] == 'X') {
            res += 9;
            i += 2;
        }
        else if (curr == 'X' && s[i + 1] == 'C') {
            cout << "xc exe" << endl;
            res += 90;
            i += 2;
        }
        else if (curr == 'X' && s[i + 1] == 'L') {
            res += 40;
            i += 2;
        }
        else if (curr == 'C' && s[i + 1] == 'D') {
            res += 400;
            i += 2;
        }
        else if (curr == 'C' && s[i + 1] == 'M') {
            res += 900;
            i += 2;
        }
        else {
            res += mp[curr];
            i += 1;
        }
    }
    return res;
}

void permuteHelper(int idx, vector<int>& nums, vector<vector<int>>& res) {
    if (idx >= nums.size()) {
        vector<int> curr = nums;
        res.push_back(curr);
        return;
    }

    for (int i = idx; i < nums.size(); i++) {
        swap(nums[idx], nums[i]);
        permuteHelper(idx + 1, nums, res);
        swap(nums[idx], nums[i]);
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    if (nums.size() == 0) {
        return {};
    }

    vector<vector<int>> res;
    permuteHelper(0, nums, res);
    return res;
}

void ndigitHelper(int idx, vector<int> nums, vector<int>& curr, vector<vector<int>>& res, int n) {
    if (idx == n) {
        res.push_back(curr);
        return;
    }

    curr[idx] = 1;
    ndigitHelper(idx + 1, nums, curr, res, n);
    curr[idx] = 2;
    ndigitHelper(idx + 1, nums, curr, res, n);
}

vector<vector<int>> ndigit(vector<int> nums, int n) {
    vector<vector<int>> res;
    vector<int> curr(n, -1);
    ndigitHelper(0, nums, curr, res, n);
    for (auto num : res) {
        for (auto n : num) {
            cout << n << "\t";
        }
        cout << endl;
    }
    return res;
}

void subsetHelper(int idx, vector<int>& nums, vector<int>& curr, vector<vector<int>>& res) {
    if (idx == nums.size()) {
        res.push_back(curr);
        return;
    }

    // pick the current element
    curr.push_back(nums[idx]);
    subsetHelper(idx + 1, nums, curr, res);
    // dont pick the current element
    curr.pop_back();
    subsetHelper(idx + 1, nums, curr, res);
}

void helper(int idx, vector<int> nums, vector<int>& curr, int currSum, int target, vector<vector<int>>& ans) {
    if (idx == nums.size()) {
        if (currSum == target) {
            ans.push_back(curr);
        }
        return;
    }

    currSum += nums[idx];
    curr.push_back(nums[idx]);
    helper(idx, nums, curr, currSum, target, ans);
    currSum -= nums[idx];
    curr.pop_back();
    helper(idx + 1, nums, curr, currSum, target, ans);
}

string addTwoStrings(string st1, string st2) {
    int carry = 0;
    string res = "";
    int n = st1.size();
    int m = st2.size();
    int len = max(n, m);
    reverse(st1.begin(), st1.end());
    reverse(st2.begin(), st2.end());

    for (int i = 0; i < len; i++) {
        int first = (i < n) ? st1[i] - '0' : 0;
        int second = (i < m) ? st2[i] - '0' : 0;

        cout << first << second << endl;
        int total = first + second + carry;
        res += to_string(total % 2);
        carry = total / 2;
        cout << total << "\t" << carry << endl;
    }

    if (carry != 0) {
        res += to_string(carry);
    }
    reverse(res.begin(), res.end());
    return res;
}

int validate(int left, int right, vector<int>& nums) {
    int max_value = -1e9;
    int min_value = 1e9;
    int n = nums.size();

    for (int i = left; i < n - right; i++) {
        max_value = max(max_value, nums[i]);
        min_value = min(min_value, nums[i]);
    }

    return max_value - min_value;
}

int minDifference(vector<int>& nums) {
    if (nums.size() <= 4) {
        return 0;
    }
    int min_diff = 1e9;
    priority_queue<int> max_h;
    priority_queue<int, vector<int>, greater<int>> min_h;
    for (auto n : nums) {
        max_h.push(n);
        min_h.push(n);
    }
    vector<int> min_four;
    vector<int> max_four;
    int i = 0;
    while (i < 4) {
        int minele = min_h.top();
        min_h.pop();
        int maxele = max_h.top();
        max_h.pop();
        min_four.push_back(minele);
        max_four.push_back(maxele);
        i += 1;
    }
    sort(min_four.begin(), min_four.end());
    sort(max_four.begin(), max_four.end());
    for (int i = 0; i < 4; i++) {
        min_diff = min(min_diff, max_four[i] - min_four[i]);
    }
    return min_diff;
}
int maximumGainHelper(string pair, int score, string& s) {
    int res = 0;
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        char curr_char = s[i];
        if (!st.empty() && st.top() == pair[0] && curr_char == pair[1])
            while (!st.empty() && st.top() == pair[0] && curr_char == pair[1]) {
                res += score;
                st.pop();
            }
        else {
            st.push(curr_char);
        }
    }
    string str1 = "";
    while (!st.empty()) {
        str1 += st.top();
        st.pop();
    }
    reverse(str1.begin(), str1.end());
    s = str1;
    return res;
}

int maximumGain(string s, int x, int y) {
    if (s.size() == 0) {
        return 0;
    }
    // x -> "ab" and y -> "ba"
    int ans = 0;
    string pair = x > y ? "ab" : "ba";
    ans += maximumGainHelper(pair, max(x, y), s);
    reverse(pair.begin(), pair.end());
    ans += maximumGainHelper(pair, min(x, y), s);
    cout << ans;
    return ans;
}

vector<int> superArray(vector<int>& A, vector<long long>& B) {
    if (A.size() == 0) {
        return {};
    }
    vector<int> nums;
    int n = A.size();
    // [1,2,3]
    for (int i = 0; i < A.size(); i++) {
        int times = (i + 1) * (n - i);
        int number = A[i];
        while (times--) {
            nums.push_back(number);
        }
    }

    sort(nums.begin(), nums.end());
    vector<int> c(B.size(), -1);
    for (int i = 0; i < B.size(); i++) {
        int idx = B[i];
        if (idx >= 0 && idx < nums.size()) {
            c[i] = nums[idx];
        }
    }

    return c;
}

int solve(int A, int B) {
    int num = A;
    int ans = 0;
    int set_bits = 0;
    int prev_set_bits = 0;
    while (num) {
        if (num & 1 == 1) {
            set_bits += 1;
        }
        num >>= 1;
    }
    ans += set_bits;
    // cout << "ans is " << ans << endl;
    prev_set_bits = set_bits;
    for (int i = A + 1; i <= B; i++) {
        if (i % 2 == 0) {
            ans += 1;
            // cout << "ans2 is " << ans << endl;
            prev_set_bits = 1;
        }
        else {
            ans += prev_set_bits + 1;
            // cout << "ans3 is " << ans << endl;
            prev_set_bits = prev_set_bits + 1;
        }

    }

    return ans;
}

bool TraversalHelper(TreeNode* root, int val, vector<char>& p) {
    if (!root) {
        return false;
    }

    if (root->val == val) {
        return true;
    }

    p.push_back('L');
    if (TraversalHelper(root->left, val, p)) {
        return true;
    }
    p.pop_back();
    p.push_back('R');

    if (TraversalHelper(root->right, val, p)) {
        return true;
    }
    p.pop_back();
    return false;
}


string getDirections(TreeNode* root, int startValue, int destValue) {
    if (root == NULL) {
        return "";
    }

    vector<char> p1;
    TraversalHelper(root, startValue, p1);
    vector<char> p2;
    TraversalHelper(root, destValue, p2);
    string res;
    vector<char> out;
    int i = 0;
    int j = 0;
    while (i < p1.size() && j < p2.size()) {
        if (p1[i] != p2[j]) {
            out.push_back('U');
            out.push_back(p2[j]);
        }
        i += 1;
        j += 1;
    }

    while (i < p1.size()) {
        out.push_back(p1[i]);
        i += 1;
    }

    while (j < p2.size()) {
        out.push_back(p2[j]);
        j += 1;
    }
    for (auto character : out) {
        cout << character << "\t";
    }
    return res;

}

void merge_helper(int left, int mid, int right, vector<int>& nums) {

    // merging two arrays
    int leftIdx = mid;
    int rightIdx = mid + 1;

    int i = left;
    int j = rightIdx;
    vector<int> out;
    while (i <= leftIdx && j <= right) {
        if (nums[i] <= nums[j]) {
            out.push_back(nums[i]);
            i += 1;
        }
        else {
            out.push_back(nums[j]) {
                j += 1;
            }
        }
    }

    while (i <= leftIdx) {
        out.push_back(nums[i]);
        i += 1;
    }

    while (j <= right) {
        out.push_back(nums[j]);
        j += 1;
    }

    for (int i = left; i <= right; i++) {
        nums[i] = out[i - left];
    }
}


void merge_sort(int left, int right, vector<int>& nums) {
    if (left > right) {
        return;
    }
    int mid = (right - left) / 2;
    merge_sort(left, mid, nums);
    merge_sort(mid + 1, right, nums);
    merge_helper(left, mid, right, nums);
}


int main() {
    // decodeString("3[a2[c]]");
    // romanToInt("III");
    // ndigit(vector<int>{1, 2}, 3);
    // cout << max_sum;
    // string st1 = "1010";
    // string st2 = "1011";
    // cout << addTwoStrings(st1, st2);
    // vector<int> nums = { 1,5,0,10,14 };
    // cout << minDifference(nums);
    // string s = "cdbcbbaaabab";
    // maximumGain(s, 4, 5);
    // vector<int> nums = { 1,2,3 };
    // vector<long long> b = { 1,2,3 };
    // superArray(nums, b);

    // cout << solve(7, 18);
    vector<int> array = { 5,4,10,2,1,8,3 };
    merge_sort(array);
    return 0;
}