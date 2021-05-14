#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

struct BigInteger {
    vector <int> represent;
    BigInteger (int x) {
        while (x > 0) {
            represent.push_back(x % 10);
            x /= 10;
        }
    }

    BigInteger (string s) {
        for (int i = (int)s.length() - 1; i >= 0; i--) represent.push_back(s[i] - '0');
    }

    void show(){
        for (int i = (int)represent.size() - 1; i >= 0; i--) cout << represent[i];
        cout << "\n";
    }

    vector <int> add (vector <int> a, vector <int> &b) {
        vector <int> c;
        while (a.size() < b.size()) a.push_back(0);
        while (b.size() < a.size()) b.push_back(0);

        int carry = 0;
        for (int i = 0; i < a.size(); i++) {
            int temp = a[i] + b[i] + carry;
            carry = temp / 10;
            temp %= 10;
            c.push_back(temp);
        }

        if (carry > 0) c.push_back(carry);
        return c;
    }
};

int lps[N];

void buildLPS (vector <int> pat) {
    int i = 1, len = 0;
    lps[0] = len;
    while (i < pat.size()) {
        if (pat[i] == pat[len]) {
            lps[i] = ++len;
            i++;
        }
        else {
            if (len) len = lps[len - 1];
            else i++;
        }
    }
}

bool makeKMP (vector <int> txt, vector <int> pat) {
    int i = 0, j = 0;
    while (i < txt.size() && j < pat.size()) {
        if (txt[i] == pat[j]) i++, j++;
        if (j == pat.size()) return true;
        else if (i < txt.size() && txt[i] != pat[j]) {
            if (j) j = lps[j - 1];
            else i++;
        }
    }

    return false;
}

string s;

int main(){
    #ifndef Futymy
        freopen("pow2in.txt", "r", stdin);
        freopen("pow2out.txt", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> s;
    if (s == "1") return cout << 0, 0;

    BigInteger start = BigInteger(1), pattern = BigInteger(s);
    buildLPS(pattern.represent);
    for (int i = 1; i < 10000; i++) {
        start.represent = start.add(start.represent, start.represent);
        if (makeKMP(start.represent, pattern.represent)) return cout << i, 0;
    }

    cout << "No solution found";
    return 0;
}
