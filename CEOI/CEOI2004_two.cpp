#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 5;

struct Data {
    int w, d;
} a[N];

long long g[N], dp[N][5]; //dp[i][j]: min cost till j-th sawmills, and the last is placed at i.
int n, f[N], w[N];

long long cost (int l, int r) { //cost of transporting l, l + 1, ..., r - 1, r to l - 1
    if (l > r) return 0;
    return g[r] - g[l - 1] - f[l - 1] * (w[r] - w[l - 1]);
}

void input(){
    scanf("%d", &n);
    for (int i = n; i >= 1; i--) scanf("%d %d", &a[i].w, &a[i].d);
}

void calc (int layer, int l, int r, int optL, int optR) {
    if (l > r) return;

    int mid = (l + r) >> 1;
    int opt = -1;

    for (int i = optL; i <= min(mid, optR); i++) {
        if (dp[mid][layer] > dp[i][layer - 1] + cost(i + 1, mid - 1)) {
            dp[mid][layer] = dp[i][layer - 1] + cost(i + 1, mid - 1);
            opt = i;
        }
    }

    calc(layer, l, mid - 1, optL, opt);
    calc(layer, mid + 1, r, opt, optR);
}

void solve(){
    f[0] = g[0] = w[0] = 0;
    memset(dp, 0x3f, sizeof(dp)); dp[0][1] = 0;

    for (int i = 1; i <= n; i++) f[i] = f[i - 1] + a[i].d;
    for (int i = 1; i <= n; i++) w[i] = w[i - 1] + a[i].w;
    for (int i = 1; i <= n; i++) g[i] = g[i - 1] + a[i].w * f[i];
    for (int j = 2; j <= 4; j++) calc(j, 0, n + 1, 0, n + 1);

    printf("%lld", dp[n + 1][4]);
}

int main(){
    input();
    solve();
    return 0;
}
