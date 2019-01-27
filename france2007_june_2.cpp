#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int ans = 0, h[N], n, subt[N];
vector <int> g[N];

void dfs (int u, int p) {
    subt[u] = 1;
    for (auto v: g[u]) if (v != p) h[v] = h[u] + 1, dfs(v, u), subt[u] += subt[v];
}

int findcen (int u, int p, int r) {
    for (auto v: g[u]) if (v != p && subt[v] * 2 >= subt[r]) return findcen(v, u, r);
    return u;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u++; v++;
        g[u].push_back(v); g[v].push_back(u);
    }

    dfs(1, 1);
    int root = findcen(1, 1, 1); h[root] = 0; dfs(root, root);
    for (auto v: g[root]) ans = max(ans, subt[v]);
    printf("%d", ans);
    return 0;
}
