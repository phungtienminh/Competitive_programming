#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

vector <int> g[N], ans;
int n, m, k;
bool visited[N], used[N];

void input(){
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(visited, 0, sizeof(visited));
    memset(used, 0, sizeof(used));
}

void dfs (int u) {
    visited[u] = true;
    if (!used[u]) {
        used[u] = true;
        if (ans.size() < k) ans.push_back(u);
        for (int v: g[u]) {
            used[v] = true;
            for (int w: g[v]) used[w] = true;
        }
    }

    for (int v: g[u]) if (!visited[v]) dfs(v);
}

void solve(){
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i);
    for (int i = 1; i <= n; i++) if (!used[i] && ans.size() < k) ans.push_back(i);
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
}

int main(){
    input();
    solve();
    return 0;
}
