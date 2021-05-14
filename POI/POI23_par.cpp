#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, dp[N], f[N];
vector <int> g[N];
bool leaf[N];

void pdfs (int u, int p) {
    int nch = 0;
    for (auto v: g[u]) {
        if (v == p) continue;
        pdfs(v, u);
        nch++;
    }

    for (auto v: g[u]) {
        if (v == p) continue;
        if (!leaf[v]) f[u] = max(f[u], f[v] + nch - 1);
    }

    int cnt = 0;
    for (auto v: g[u]) {
        if (v == p) continue;
        if (leaf[v]) cnt++;
    }

    f[u] = max(f[u], cnt);

    if (!nch) leaf[u] = true;
}

void dfs (int u, int p) {
    int max1 = 0, max2 = 0, nch = 0;
    for (auto v: g[u]) {
        if (v == p) continue;
        nch++;
        dfs(v, u);
    }

    for (auto v: g[u]) {
        if (v == p) continue;

        if (f[v] > max1) {
            max2 = max1;
            max1 = f[v];
        }
        else if (f[v] > max2) max2 = f[v];
    }

    if (!nch) return;

    dp[u] = max(dp[u], max1 + (int)g[u].size() - 1);
    if (nch >= 2) dp[u] = max(dp[u], max1 + max2 + (int)g[u].size() - 2);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    pdfs(1, 1);
    dfs(1, 1);
    #ifdef Futymy
        for (int i = 1; i <= n; i++) cout << dp[i] << " ";
        cout << "\n";
    #endif // Futymy
    printf("%d", *max_element(dp + 1, dp + n + 1));
    return 0;
}
