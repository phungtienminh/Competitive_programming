#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, m, a[N], dp[N], rmq[15][N];

int query (int u, int v) {
    int k = log2(v - u + 1);
    return max(rmq[k][u], rmq[k][v - (1 << k) + 1]);
}

int main(){
    #ifndef Futymy
        freopen("teamwork.in", "r", stdin);
        freopen("teamwork.out", "w", stdout);
    #endif // Futymy
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), rmq[0][i] = a[i];
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            rmq[k][i] = max(rmq[k - 1][i], rmq[k - 1][i + (1 << (k - 1))]);
        }
    }

    memset(dp, -0x3f, sizeof(dp)); dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = max(0, i - m); j < i; j++) {
            dp[i] = max(dp[i], dp[j] + query(j + 1, i) * (i - j));
        }
    }

    printf("%d", dp[n]);
    return 0;
}
