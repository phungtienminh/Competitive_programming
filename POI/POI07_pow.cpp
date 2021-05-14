#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 6;
const int maxn = 2005;
const int base = 317;
const int mod1 = 1e9 + 2277;
const int mod2 = 1e9 + 5277;

pair <int, int> Hash[N][maxn], pw[maxn];
string a[N];
map <pair <int, int>, int> mm;

pair <int, int> get_hash (int i, int l, int r) {
    int p1 = (Hash[i][r].first - Hash[i][l - 1].first * pw[r - l + 1].first) % mod1;
    if (p1 < 0) p1 += mod1;

    int p2 = (Hash[i][r].second - Hash[i][l - 1].second * pw[r - l + 1].second) % mod2;
    if (p2 < 0) p2 += mod2;

    return make_pair(p1, p2);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    pw[0] = make_pair(1, 1);
    for (int i = 1; i < maxn; i++) {
        pw[i].first = (pw[i - 1].first * base) % mod1;
        pw[i].second = (pw[i - 1].second * base) % mod2;
    }

    int n;
    cin >> n;

    int min_len = 2005;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        min_len = min(min_len, (int)a[i].length());
    }

    for (int i = 1; i <= n; i++) a[i] = "#" + a[i];
    for (int i = 1; i <= n; i++) {
        Hash[i][0] = make_pair(0, 0);
        for (int j = 1; j <= a[i].length(); j++) {
            Hash[i][j].first = (Hash[i][j - 1].first * base + a[i][j]) % mod1;
            Hash[i][j].second = (Hash[i][j - 1].second * base + a[i][j]) % mod2;
        }
    }

    int l = 1;
    int r = min_len;

    while (l <= r) {
        int len = (l + r) / 2;

        mm.clear();
        for (int i = 1; i <= n; i++) {
            set <pair <int, int> > st;
            for (int j = 1; j <= (int)a[i].length() - len; j++) {
                pair <int, int> res = get_hash(i, j, j + len - 1);
                if (st.find(res) != st.end()) continue;

                st.insert(res);
                mm[res]++;
            }
        }

        bool ok = false;
        for (map <pair <int, int>, int>::iterator it = mm.begin(); it != mm.end(); it++) {
            if (it->second == n) {
                ok = true;
                break;
            }
        }

        if (ok) l = len + 1;
        else r = len - 1;
    }

    cout << r;
    return 0;
}
