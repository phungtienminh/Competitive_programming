#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 5;

int n, m, deg[N];
vector <pair <int, int> > g[N], tree[N];
bool used[N], visited[N];
vector <pair <int, int> > res;
vector <int> trace[N];
pair <int, int> par[N], edge[N];

void dfs (int u, int p) {
    visited[u] = true;
    for (auto v: g[u]) {
        if (visited[v.second]) continue;
        used[v.first] = true;
        tree[u].push_back({v.first, v.second});
        par[v.second] = {u, v.first};
        dfs(v.second, u);
    }
}

void solve (int u, int org) {
    visited[u] = true;
    for (auto v: tree[u]) solve(v.second, org);
    if (u == org) return;
    if (deg[u] % 2 == 1) {
        deg[u]++;
        trace[u].push_back(par[u].second);
    }
    else {
        deg[par[u].first]++;
        trace[par[u].first].push_back(par[u].second);
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back({i, v + n});
        g[v + n].push_back({i, u});
        edge[i] = {u, v};
    }

    memset(par, -1, sizeof(par));
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i, i);
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            deg[edge[i].second + n]++;
            trace[edge[i].second + n].push_back(i);
        }
    }
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= n; i++) if (!visited[i]) solve(i, i);
    for (int i = 1; i <= n + n; i++) for (int j = 0; j + 1 < trace[i].size(); j += 2) res.push_back({trace[i][j], trace[i][j + 1]});
    printf("%d\n", (int)res.size());
    for (auto i: res) printf("%d %d\n", i.first, i.second);
    return 0;
}
/*
6
4 5
4 5
2 2
2 6
4 3
3 5
*/
