#include <bits/stdc++.h>
using namespace std;

vector<string> commonChars(vector<string>& words) {
    if (words.size() == 0) {
        return {};
    }
    vector<int> pre(26, 0);
    vector<int> current(26, 0);

    for (int i = 0; i < words[0].size(); i++) {
        char character = words[0][i];
        pre[character - 'a'] += 1;
    }

    vector<int> r(26, 0);
    for (int i = 1; i < words.size(); i++) {
        r.assign(26, 0);
        for (int j = 0; j < words[i].size(); j++) {
            char character = words[i][j];
            current[character - 'a'] += 1;
        }
        for (int k = 0; k < 26; k++) {
            if (pre[k] > 0 && current[k] > 0) {
                r[k] = min(pre[k], current[k]);
            }
        }
        pre = r;
        current.assign(26, 0);
    }
    vector<string> resultant;
    for (int i = 0; i < 26; i++) {
        if (r[i] > 0) {
            for (int j = 0; j < r[i]; j++) {
                char character = (i + 97);
                resultant.push_back(string(1, character));
            }
        }
    }
    return resultant;
}

// { 4, 3, 1, 2 };
bool isArraySpecial(int start, int end, vector<int>& nums) {
    if (start == end) {
        return true;
    }
    cout << start << " " << end << endl;
    for (int i = start + 1; i <= end; i++) {
        int firstNum = nums[i - 1];
        int secondNum = nums[i];
        if ((firstNum % 2 == 0 && secondNum % 2 == 0) || (firstNum % 2 == 1 && secondNum % 2 == 1)) {
            return false;
        }
    }

    return true;
}

vector<bool> isArraySpecial2(vector<int>& nums, vector<vector<int>>& queries) {
    vector<bool> res;
    int n = queries.size();
    for (int i = 0; i < n; i++) {
        int start = queries[i][0];
        int end = queries[i][1];

        if (isArraySpecial(start, end, nums) == true) {
            res.push_back(true);
        }
        else {
            res.push_back(false);
        }
    }
    for (auto r : res) {
        cout << r << "\t";
    }
    return res;
}



int main() {
    // cout << "welcome";
    // vector<string> words = { "bella", "label", "roller" };
    // vector<string> res = commonChars(words);
    // for (auto str : res) {
    //     cout << str << "\t";
    // }
    vector<int> nums = { 3,4,1,2,6 };
    vector<vector<int>> queries = { {0,4} };
    isArraySpecial2(nums, queries);
    return 0;
}