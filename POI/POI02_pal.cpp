#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2005;
const int mod = 1000000007;

string s;
int pw[N], Hash[N], Hash_rev[N], f[N], g[N], trace_f[N], trace_g[N];

int get_hash (int l, int r) {
    return ((Hash[r] - Hash[l - 1] * pw[r - l + 1]) % mod + mod) % mod;
}

int get_hash_rev (int l, int r) {
    return ((Hash_rev[r] - Hash_rev[l - 1] * pw[r - l + 1]) % mod + mod) % mod;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    int n = s.length();

    pw[0] = 1;
    Hash[0] = Hash_rev[0] = 0;

    for (int i = 1; i < N; i++) pw[i] = (pw[i - 1] * 26) % mod;
    for (int i = 1; i <= n; i++) Hash[i] = (Hash[i - 1] * 26 + s[i - 1] - 'a') % mod;
    for (int i = 1; i <= n; i++) Hash_rev[i] = (Hash_rev[i - 1] * 26 + s[n - i] - 'a') % mod;

    memset(f, 0x3f, sizeof(f));
    memset(g, -1, sizeof(g));

    f[0] = g[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (f[j] < 1e9) {
                if ((i - j) % 2 == 0 && get_hash(j + 1, i) == get_hash_rev(n - i + 1, n - j)) {
                    if (f[i] > f[j] + 1) {
                        f[i] = f[j] + 1;
                        trace_f[i] = j;
                    }
                }
            }
            if (g[j] != -1) {
                if ((i - j) % 2 == 0 && get_hash(j + 1, i) == get_hash_rev(n - i + 1, n - j)) {
                    if (g[i] < g[j] + 1) {
                        g[i] = g[j] + 1;
                        trace_g[i] = j;
                    }
                }
            }
        }
    }

    //cout << get_hash(1, 6) << " " << get_hash_rev(n - 5, n) << "\n";

    /*for (int i = 0; i <= n; i++) cout << (f[i] > 1e18 ? -1 : f[i]) << " ";
    cout << "\n";
    for (int i = 0; i <= n; i++) cout << g[i] << " ";
    cout << "\n";*/

    if (g[n] == -1) cout << "NIE\n";
    else {
        vector <string> ans_f, ans_g;
        int pos = n;

        while (pos > 0) {
            ans_f.push_back(s.substr(trace_f[pos], pos - trace_f[pos]));
            pos = trace_f[pos];
        }

        pos = n;
        while (pos > 0) {
            ans_g.push_back(s.substr(trace_g[pos], pos - trace_g[pos]));
            pos = trace_g[pos];
        }

        for (int i = (int)ans_f.size() - 1; i >= 0; i--) {
            cout << ans_f[i];
            if (i) cout << " ";
        }
        cout << "\n";
        for (int i = (int)ans_g.size() - 1; i >= 0; i--) {
            cout << ans_g[i];
            if (i) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
