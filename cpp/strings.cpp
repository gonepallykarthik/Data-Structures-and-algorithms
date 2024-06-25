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

int main() {
    // decodeString("3[a2[c]]");
    romanToInt("III");
    return 0;
}