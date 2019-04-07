#include <bits/stdc++.h>

using namespace std;

int t;
string s, a, b = "";

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int T = 1; T <= t; T++) {
        cin >> s; a = ""; b = "";
        bool full = true;
        for (int i = 0; i < s.length(); i++) if (s[i] != '1') full = false;

        if (full) {
            a = s;
            b = "1";
            a[a.length() - 1] = '0';
            cout << "Case #" << T << ": " << a << " " << b << "\n";
            continue;
        }

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0') a += '0', b += '0';
            else if (s[i] == '5') a += '2', b += '3';
            else a += '1', b += (char)(s[i] - '1' + '0');
        }

        while (b.length() > 1 && b[0] == '0') b.erase(0, 1);
        cout << "Case #" << T << ": " << a << " " << b << "\n";
    }
    return 0;
}
