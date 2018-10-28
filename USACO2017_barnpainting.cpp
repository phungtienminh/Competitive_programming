#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

void add (int &x, int y) {
    x = (x + y) % mod;
}

int n, k, c[N], dp[N][4];
vector <int> g[N];

void dfs (int u, int p) {
    if (c[u]) dp[u][c[u]] = 1;
    else dp[u][1] = dp[u][2] = dp[u][3] = 1;

    if (c[u]) {
        for (auto v: g[u]) {
            if (v == p) continue;
            if (c[v] == c[u]) return;
            dfs(v, u);
        }

        for (auto v: g[u]) {
            if (v == p) continue;
            if (!c[v]) {
                if (c[u] == 1) dp[u][c[u]] = (1LL * dp[u][c[u]] * (dp[v][2] + dp[v][3])) % mod;
                else if (c[u] == 2) dp[u][c[u]] = (1LL * dp[u][c[u]] * (dp[v][1] + dp[v][3])) % mod;
                else dp[u][c[u]] = (1LL * dp[u][c[u]] * (dp[v][1] + dp[v][2])) % mod;
            }
            else dp[u][c[u]] = (1LL * dp[u][c[u]] * dp[v][c[v]]) % mod;
        }
    }
    else {
        for (auto v: g[u]) {
            if (v == p) continue;
            dfs(v, u);
        }

        for (int i = 1; i <= 3; i++) {
            for (auto v: g[u]) {
                if (v == p) continue;
                if (!c[v]) {
                    if (i == 1) dp[u][1] = (1LL * dp[u][1] * (dp[v][2] + dp[v][3])) % mod;
                    else if (i == 2) dp[u][2] = (1LL * dp[u][2] * (dp[v][1] + dp[v][3])) % mod;
                    else dp[u][3] = (1LL * dp[u][3] * (dp[v][1] + dp[v][2])) % mod;
                }
                else {
                    if (i != c[v]) dp[u][i] = (1LL * dp[u][i] * dp[v][c[v]]) % mod;
                    else dp[u][i] = 0;
                }
            }
        }
    }
}

int main(){
    #ifndef Futymy
        freopen("barnpainting.in", "r", stdin);
        freopen("barnpainting.out", "w", stdout);
    #endif // Futymy
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }

    for (int i = 1; i <= k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        c[x] = y;
    }

    dfs(1, 1);
    int ans = 0;
    for (int i = 1; i <= 3; i++) add(ans, dp[1][i]);
    printf("%d", ans);
    return 0;
}
