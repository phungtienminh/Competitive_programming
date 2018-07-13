#include <bits/stdc++.h>

using namespace std;

const int N = 30005;
const int M = 16;

int h[N], par[M][N], n;
vector <int> g[N];

void dfs (int u, int p) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;

        h[v] = h[u] + 1;
        par[0][v] = u;
        dfs(v, u);
    }
}

void makeLCA(){
    for (int i = 1; i < M; i++) {
        for (int j = 1; j <= n; j++) {
            par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
}

int LCA (int x, int y) {
    if (h[x] > h[y]) swap(x, y);
    for (int i = M - 1; i >= 0; i--) {
        if (par[i][y] != -1 && h[y] - (1 << i) >= h[x]) {
            y = par[i][y];
        }
    }

    if (x == y) return x;
    for (int i = M - 1; i >= 0; i--) {
        if (par[i][x] != -1 && par[i][y] != -1 && par[i][x] != par[i][y]) {
            x = par[i][x];
            y = par[i][y];
        }
    }

    if (x == y) return x;
    return par[0][x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    h[1] = 0; memset(par, -1, sizeof(par));
    dfs(1, 1);
    makeLCA();

    int ans = 0;
    int cur = 1;
    int m; cin >> m;
    while (m--) {
        int x; cin >> x;
        ans = ans + h[x] + h[cur] - 2 * h[LCA(x, cur)];
        cur = x;
    }

    cout << ans;
    return 0;
}
