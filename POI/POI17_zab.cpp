#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, k, p, par[2][N], ans[N];
long long m, a[N];

void input(){
    scanf("%d %d %lld", &n, &k, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
}

void solve(){
    int l = 1;
    int r = k + 1;
    for (int i = 1; i <= n; i++) {
        while (r < n && a[i] - a[l] > a[r + 1] - a[i]) l++, r++;

        if (a[i] - a[l] >= a[r] - a[i]) par[0][i] = l;
        else par[0][i] = r;
    }

    for (int i = 1; i <= n; i++) ans[i] = i;
    for (int i = 0; i <= 61; i++) {
        int cur = i & 1;
        int prev = cur ^ 1;

        for (int j = 1; j <= n; j++) if (i != 0) par[cur][j] = par[prev][par[prev][j]];
        if (m & (1LL << i)) {
            for (int j = 1; j <= n; j++) ans[j] = par[cur][ans[j]];
        }
    }

    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
}

int main(){
    input();
    solve();
    return 0;
}
