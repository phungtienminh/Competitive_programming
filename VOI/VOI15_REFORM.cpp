#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, cnt = 0, num[N], low[N], par[N], nbridge = 0, sz = 0;
long long ans = 0;
vector <int> g[N], vec;
bool visited[N];

void predfs (int u) {
    visited[u] = true; sz++;
    for (auto v: g[u]) if (!visited[v]) predfs(v);
}

int dfs (int u) {
    num[u] = low[u] = ++cnt;
    int child = 0;
    for (auto v: g[u]) {
        if (!num[v]) {
            par[v] = u;
            int nchild = dfs(v);
            child += nchild;
            low[u] = min(low[u], low[v]);
            if (num[u] < low[v]) {
                ans += 1LL * nchild * (n - nchild) - 1;
                nbridge++;
            }
        }
        else if (v != par[u]) low[u] = min(low[u], num[v]);
    }

    return child + 1;
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) if (!visited[i]) sz = 0, predfs(i), vec.push_back(sz);
    if (vec.size() > 2) return !printf("%d", 0);
    for (int i = 1; i <= n; i++) if (!num[i]) dfs(i);
    if (vec.size() == 2) return !printf("%lld", 1LL * vec[0] * vec[1] * (m - nbridge));
    else printf("%lld", ans + 1LL * (m - nbridge) * (1LL * n * (n - 1) / 2 - m));
    return 0;
}
