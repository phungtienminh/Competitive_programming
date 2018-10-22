#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, m, k, a[N];
long long dp[N][32];
vector <int> g[N];

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) dp[i][1 << (a[i] - 1)] = 1;
    for (int i = 1; i < 32; i++) {
        for (int j = 1; j <= n; j++) {
            if (dp[j][i]) {
                for (auto v: g[j]) {
                    if (i & (1 << (a[v] - 1))) continue;
                    dp[v][i | (1 << (a[v] - 1))] += dp[j][i];
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j < 32; j++) ans += dp[i][j];
    printf("%lld", ans - n);
    return 0;
}
