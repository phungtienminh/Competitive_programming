#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, m, k, ans = 1e9;
string s, a[N];

int solve (string t) {
    int res = 1e9;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = i; j < i + m; j++) {
            cnt += (s[j % n] != t[j - i]);
        }

        res = min(res, cnt);
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k >> s;
    for (int i = 1; i <= k; i++) cin >> a[i];
    for (int i = 1; i <= k; i++) ans = min(ans, solve(a[i]));
    cout << ans;
    return 0;
}
