#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector <int> g[N];
int a[N], dp[N], pref[N];
long long f[25][2], ans = 0;
bool visited[N];

void dfs (int u, int p) {
    dp[u] = 1;
    for (auto v: g[u]) {
        if (visited[v] || v == p) continue;
        dfs(v, u);
        dp[u] += dp[v];
    }
}

int find_centroid (int u, int p, int sz) {
    for (auto v: g[u]) {
        if (v != p && !visited[v] && dp[v] > sz/2) return find_centroid(v, u, sz);
    }

    return u;
}

void redfs (int u, int p) {
    ans += pref[u];
    for (int i = 0; i < 25; i++) ans = ans + (1LL << i) * f[i][(pref[u] >> i & 1LL) ^ 1LL];
    for (auto v: g[u]) {
        if (visited[v] || v == p) continue;
        pref[v] = pref[u] ^ a[v];
        redfs(v, u);
    }
}

void redfs_2 (int u, int p, int val) {
    for (int i = 0; i < 25; i++) f[i][pref[u] >> i & 1LL] += val;
    for (auto v: g[u]) {
        if (visited[v] || v == p) continue;
        pref[v] = pref[u] ^ a[v];
        redfs_2(v, u, val);
    }
}

void centroid (int root) {
    dfs(root, root);
    int cen = find_centroid(root, root, dp[root]);
    visited[cen] = true;

    for (auto v: g[cen]) {
        if (visited[v]) continue;

        pref[v] = a[cen] ^ a[v];
        redfs(v, cen);

        pref[v] = a[v];
        redfs_2(v, cen, 1);
    }

    for (auto v: g[cen]) {
        if (visited[v]) continue;

        pref[v] = a[v];
        redfs_2(v, cen, -1);
    }

    for (auto v: g[cen]) {
        if (!visited[v]) centroid(v);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ans += a[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    centroid(1);
    printf("%lld", ans);
    return 0;
}
