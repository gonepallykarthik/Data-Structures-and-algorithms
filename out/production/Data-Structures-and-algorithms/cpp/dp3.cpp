#include <bits/stdc++.h>
using namespace std;

int LongestIncreasingSequence(vector<int> nums) {
    if (nums.size() == 0) {
        return -1;
    }

    vector<int> dp(nums.size(), 1);
    int maxi = INT_MIN;
    for (int i = 1; i < nums.size(); i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], 1 + dp[j]);
                maxi = max(maxi, dp[i]);
            }
        }
    }
    return maxi;
}

class Box {
public:
    int length;
    int width;
    int height;

    Box(int l, int w, int h) {
        length = l;
        width = w;
        height = h;
    }

    // Overload the < operator for comparison
    bool operator<(const Box& other) const {
        if (length != other.length) return length < other.length;
        if (width != other.width) return width < other.width;
        return height < other.height;
    }
};

bool canBeStacked(vector<int>& top, vector<int>& bottom) {
    return top[0] < bottom[0] && top[1] < bottom[1];
}

void printMap(map<Box, int>& mp) {
    for (auto it = mp.begin(); it != mp.end(); it++) {
        cout << it->second << "\t";
    }
}


//  dp -> hard problem  ******* BOX STACKING ********
int maxHeightPossible(vector<vector<int>> boxes) {
    sort(boxes.begin(), boxes.end(), [](const vector<int>& a, const vector<int>& b) {
        return (a[0] * a[1]) < (b[0] * b[1]);
        });

    map<Box, int> mp;
    for (const auto& box : boxes) {
        int length = box[0];
        int width = box[1];
        int height = box[2];
        Box b(length, width, height);
        mp.insert({ b, height });
    }


    for (int i = 1; i < boxes.size(); i++) {
        vector<int> bottom_box = boxes[i];
        Box b(bottom_box[0], bottom_box[1], bottom_box[2]);
        vector<Box*> s;
        for (int j = 0; j < i; j++) {
            if (canBeStacked(boxes[j], bottom_box)) {
                s.push_back(new Box(boxes[j][0], boxes[j][1], boxes[j][2]));
            }
        }
        for (auto& box : s) {
            Box temp(box->length, box->width, box->height);
            mp[b] = max(mp[b], bottom_box[2] + mp[temp]);
        }
    }
    int max_height = 0;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        max_height = max(max_height, it->second);
    }
    return max_height;
}

int maxHeight(vector<vector<int>>& cuboids) {
    if (cuboids.size() == 0) {
        return 0;
    }
    for (vector<int>& cuboid : cuboids) {
        sort(cuboid.begin(), cuboid.end());
    }
    sort(cuboids.begin(), cuboids.end());
    int n = cuboids.size();
    vector<int> currentCuboid = cuboids[n - 1];
    int height = currentCuboid[2];
    for (int i = n - 2; i >= 0; i--) {
        if (cuboids[i][0] <= currentCuboid[0] && cuboids[i][1] <= currentCuboid[1] && cuboids[i][2] <= currentCuboid[2]) {
            height += cuboids[i][2];
        }
    }
    return height;
}

int LISHelper(int idx, vector<int>& nums, int n, int prevIdx) {
    if (idx == n) {
        return 0;
    }

    int take = 0;
    if (prevIdx == -1 || nums[prevIdx] < nums[idx]) {
        take = 1 + LISHelper(idx + 1, nums, n, idx);
    }
    int notTake = 0 + LISHelper(idx + 1, nums, n, prevIdx);

    return max(take, notTake);
}


// dp approach
int LIS(vector<int> nums) {
    int n = nums.size();
    return LISHelper(0, nums, n, -1);
}

int cutSgementsHelper(int n, int x, int y, int z) {
    if (n == 0) {
        return 0;
    }

    int X = INT_MIN;
    if (n - x >= 0) {
        X = 1 + cutSgementsHelper(n - x, x, y, z);
    }
    int Y = INT_MIN;
    if (n - y >= 0) {
        Y = 1 + cutSgementsHelper(n - y, x, y, z);
    }
    int Z = INT_MIN;
    if (n - z >= 0) {
        Z = 1 + cutSgementsHelper(n - z, x, y, z);
    }
    return max(X, max(Y, Z));
}


int cutSegments(int n, int x, int y, int z) {
    return cutSgementsHelper(n, x, y, z);
}

int perfectSquare(int n) {
    if (n == 0) {
        return 0;
    }

    // if (dp[n] != -1) {
    //     return dp[n];
    // }

    int ans = INT_MAX;
    for (int j = 1; j * j <= n; j++) {
        int subProblems = 1 + perfectSquare(n - j * j);
        ans = min(ans, subProblems);
    }
    // dp[n] = ans;
    return ans;
}

int findLongestChainHelper(int idx, vector<vector<int>>& pairs, int prevEnd, vector<vector<int>>& dp) {
    if (idx >= pairs.size()) {
        return 0;
    }

    if (dp[idx][prevEnd + 1] != -1) {
        return dp[idx][prevEnd + 1];
    }

    int pick = 0;
    if (prevEnd == -1 || pairs[idx][0] > pairs[prevEnd][1]) {
        pick = 1 + findLongestChainHelper(idx + 1, pairs, idx, dp);
    }
    int dontPick = 0 + findLongestChainHelper(idx + 1, pairs, prevEnd, dp);
    dp[idx][prevEnd + 1] = max(pick, dontPick);
    return dp[idx][prevEnd + 1];
}

int findLongestChain(vector<vector<int>>& pairs) {
    int n = pairs.size();
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return findLongestChainHelper(0, pairs, -1, dp);
}


int main() {
    // cout << "welcome to this application";
    // vector<int> nums = { 3,1,8,2,5 };
    // int res = LongestIncreasingSequence(nums);
    // cout << res;
    // vector<vector<int>> boxes = { {4,5,3}, {1,2,2}, {2,3,2}, {1,5,4}, {2,4,1}, {3,6,2} };
    // vector<vector<int>> boxes = { {7,6,4}, {3,2,1}, {6,5,4}, {32,12,10} };
    // int r = maxHeightPossible(boxes);
    // cout << r;
    // cout << LIS(vector<int>{5, 8, 3, 7, 9, 1});
    // cout << cutSegments(8, 3, 3, 3);
    // cout << perfectSquare(13);
    vector<vector<int>> pairs = { {1,2}, {2,3}, {3,4} };
    cout << findLongestChain(pairs);
    return 0;
}