#include <bits/stdc++.h>
using namespace std;


vector<vector<string>> getAnagrams(vector<string> A) {

    map<string, vector<string>> mp;
    for (auto str : A) {
        string org = str;
        sort(str.begin(), str.end());
        if (mp.find(str) != mp.end()) {
            mp[str].push_back(org);
        }

        else {
            mp[str] = { org };
        }
    }

    vector<vector<string>> res;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        res.push_back(it->second);
    }

    for (auto r1 : res) {
        sort(r1.begin(), r1.end());
    }

    for (auto r1 : res) {
        for (auto r : r1) {
            cout << r << "\t";
        }
        cout << endl;

    }

    return res;
}

int calculateTime(vector<int> A, int t) {
    int time = 0;
    cout << "exe" << endl;
    int n = A.size();
    for (int i = 0; i < n; i++) {
        int time_taken = ceil((double)A[i] / (double)t);
        cout << time_taken << "\t";
    }
    cout << endl;
    return time;
}



int main() {
    // getAnagrams(vector<string> {"eat", "tea", "ate", "tan", "nat", "bat"});
    int r = calculateTime(vector<int>{3, 6, 7, 11}, 2);
    cout << r << endl;
    return 0;
}