#include <bits/stdc++.h>

using namespace std;

const int N = 5005;
const int mod = 1e9 + 7;

int n, m, k, dp[N], ans = 1, cnt[26];
vector <int> syllables, sumdp, type[N];

void add (int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

void mul (int &x, int y) {
    x = 1LL * x * y % mod;
}

int binPow (int x, int y) {
    int ans = 1;
    while (y > 0) {
        if (y & 1) ans = 1LL * ans * x % mod;
        x = 1LL * x * x % mod;
        y >>= 1;
    }

    return ans;
}

int main(){
    #ifndef Futymy
        freopen("poetry.in", "r", stdin);
        freopen("poetry.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        int nsyl, ntype;
        cin >> nsyl >> ntype;
        syllables.push_back(nsyl);
        type[ntype].push_back(nsyl);
    }

    dp[0] = 1;
    for (int i = 1; i <= k; i++) {
        for (auto j: syllables) {
            if (i >= j) add(dp[i], dp[i - j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (type[i].size() == 0) continue;
        int sum = 0;

        for (auto j: type[i]) add(sum, dp[k - j]);
        sumdp.push_back(sum);
    }

    for (int i = 1; i <= m; i++) {
        char c;
        cin >> c;
        cnt[c - 'A']++;
    }

    for (int i = 0; i < 26; i++) {
        if (!cnt[i]) continue;
        int res = 0;

        for (auto j: sumdp) add(res, binPow(j, cnt[i]));
        mul(ans, res);
    }

    cout << ans;
    return 0;
}
