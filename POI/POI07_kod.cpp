#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 20;
int dp[N], C[2 * N][2 * N];

void solve (char c, int n, int k, string &ans, int pos) {
    if (k == 0) return;

    int cur = 0;
    while (dp[cur] * dp[k - 1 - cur] <= n) {
        n = n - dp[cur] * dp[k - 1 - cur];
        cur++;
    }

    ans[pos] = c + cur;
    solve(c, n / dp[k - 1 - cur], cur, ans, pos + 1);
    solve(c + cur + 1, n % dp[k - 1 - cur], k - 1 - cur, ans, pos + cur + 1);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < N * 2; i++) {
        for (int j = 0; j <= i; j++) {
            if (!i || !j || i == j) C[i][j] = 1;
            else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }

    for (int i = 0; i < N; i++) dp[i] = C[2 * i][i] / (i + 1);

    string ans = "";
    for (int i = 0; i < k; i++) ans += '-';
    solve('a', n - 1, k, ans, 0);
    cout << ans;
    return 0;
}
