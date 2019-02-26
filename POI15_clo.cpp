#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, deg[N], ans[N];
set <int> g[N];
bool visited[N];
set <pair <int, int> > S;

bool dfs (int u, int p) {
    visited[u] = true;
    for (auto it: g[u]) {
        if (visited[it] && it == p) continue;
        if (visited[it]) return true;
        if (dfs(it, u)) return true;
    }

    return false;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++; deg[v]++;
        g[u].insert(v); g[v].insert(u);
    }

    for (int i = 1; i <= n; i++) if (!visited[i] && !dfs(i, i)) return cout << "NIE", 0;
    for (int i = 1; i <= n; i++) S.insert({deg[i], i});

    while (!S.empty()) {
        auto it = S.begin(); //cout << (*it).second << "\n";
        int u = (*it).second;
        auto it2 = g[u].begin();
        int v = (*it2);
        deg[u]--; deg[v]--;
        if (!ans[u]) ans[u] = v;
        else if (!ans[v]) ans[v] = u;
        g[u].erase(it2); g[v].erase(g[v].find(u));
        S.erase(it); S.erase(S.find({deg[v] + 1, v}));
        if (deg[u]) S.insert({deg[u], u});
        if (deg[v]) S.insert({deg[v], v});
        //break;
    }

    cout << "TAK\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
    return 0;
}
