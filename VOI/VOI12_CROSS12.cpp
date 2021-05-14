#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
const int maxn = 105;

int n, m, a[N], dp[N], cross[maxn];
string s;

int get (int step) {
    int cur = 0, ans = 0;
    while (cur <= m) {
        cur += step;
        ans++;

        while (cur <= m && s[cur] == '1') cur--;
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> s; s = "0" + s;
    for (int i = 1; i <= n; i++) cross[a[i]] = get(a[i]);
    for (int i = 1; i <= n; i++) a[i] = cross[a[i]];
    sort(a + 1, a + n + 1);
    dp[1] = a[1]; dp[2] = a[2];
    for (int i = 3; i <= n; i++) dp[i] = min(dp[i - 1] + a[1] + a[i], dp[i - 2] + a[2] + a[i] + a[1] + a[2]);
    cout << dp[n];
    return 0;
}
