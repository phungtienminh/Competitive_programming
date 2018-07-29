#include <bits/stdc++.h>

using namespace std;

const int N = 605;
const int K = 55;

int n, m, a[N][N], pref[N][N], dp[N][K], trace[N][K];

int cost (int l, int r) {
    return pref[r][n] - pref[l][n] - pref[r][r] + pref[l][r];
}

void input(){
    scanf("%d %d", &n, &m);
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}

void solve(){
    memset(pref, 0, sizeof(pref));
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            sum += a[i][j];
            pref[i][j] = pref[i - 1][j] + sum;
        }
    }

    memset(dp, -0x3f, sizeof(dp));
    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) {
                if (dp[k][j - 1] > -1e9) {
                    if (dp[i][j] < dp[k][j - 1] + cost(k, i)) {
                        dp[i][j] = dp[k][j - 1] + cost(k, i);
                        trace[i][j] = k;
                    }
                }
            }
        }
    }

    int ans = -1e9;
    int pos = 0;
    for (int i = 0; i <= n; i++) {
        if (ans < dp[i][m]) {
            ans = dp[i][m];
            pos = i;
        }
    }

    vector <int> res;
    int choose = m;
    while (pos > 0) {
        res.push_back(pos);
        pos = trace[pos][choose--];
    }

    for (int i = (int)res.size() - 1; i >= 0; i--) printf("%d ", res[i]);
}

int main(){
    input();
    solve();
    return 0;
}
