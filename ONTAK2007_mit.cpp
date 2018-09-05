#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
const int inf = -1e9 - 2277;

int n, q, dp[N][2];
bool ok[N];
vector <int> g[N];

void dfs (int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = -1e9;

    int sum = 0;
    for (int v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        sum += dp[v][0];
    }

    dp[u][0] = sum;
    int mx = -1e9, mx2 = -1e9;

    for (int v: g[u]) {
        if (v == p) continue;
        if (dp[v][1] < -5e8) continue;

        if (dp[v][1] - dp[v][0] > mx) {
            mx2 = mx;
            mx = dp[v][1] - dp[v][0];
        }
        else if (dp[v][1] - dp[v][0] > mx2) mx2 = dp[v][1] - dp[v][0];
    }

    if (mx2 > -5e8 && mx > -5e8) dp[u][0] = max(dp[u][0], 1 + mx2 + mx + sum);
    if (ok[u] && mx > -5e8) dp[u][0] = max(dp[u][0], 1 + mx + sum);
    if (ok[u]) dp[u][1] = sum;
    if (mx > -5e8) dp[u][1] = max(dp[u][1], sum + mx);

    dp[u][0] = max(dp[u][0], dp[u][1]);
}

int main(){
    scanf("%d", &n);
    memset(ok, 0, sizeof(ok));

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int x;
        scanf("%d", &x);
        ok[x] = true;
    }

    dfs(1, 1);
    printf("%d", dp[1][0]);
    return 0;
}
