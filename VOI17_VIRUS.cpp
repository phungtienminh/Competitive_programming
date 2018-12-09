#include <bits/stdc++.h>

using namespace std;

int t, k;
string s;

int main(){
    #ifndef Futymy
        freopen("virus.inp", "r", stdin);
        freopen("virus.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t >> s;
    while (t--) {
        cin >> k;
        int n = s.length();

        bool ok = false;
        for (int len = n / 2; len >= 1; len--) {
            int ans = 0;
            for (int i = 0; i + 2 * len - 1 < n; i++) {
                for (int j = i; j <= i + len - 1; j++) {
                    if (s[j] != s[j + len]) ans++;
                }

                break;
            }

            if (ans <= k) {
                cout << len << "\n";
                ok = true;
                break;
            }

            bool f = false;
            for (int i = 1; i + 2 * len - 1 < n; i++) {
                if (s[i - 1] != s[i - 1 + len]) ans--;
                if (s[i + len - 1] != s[i + 2 * len - 1]) ans++;

                if (ans <= k) {
                    f = true;
                    break;
                }
            }

            if (f) {
                cout << len << "\n";
                ok = true;
                break;
            }
        }

        if (!ok) cout << 0 << "\n";
    }
    return 0;
}
