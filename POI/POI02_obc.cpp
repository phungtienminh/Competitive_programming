#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

int h[N], n;
vector <int> g[N];

void dfs (int u, int p) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;

        h[v] = h[u] + 1;
        dfs(v, u);
    }
}

void solve (int u, int p) {
    if (h[u] % 2 == 1) cout << u << '\n';
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;

        solve(v, u);
    }

    if (h[u] % 2 == 0) cout << u << '\n';
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

    h[1] = 0;
    dfs(1, 1);
    solve(1, 1);
    return 0;
}
