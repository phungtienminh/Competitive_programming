#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m;
vector <int> g[N];
bool visited[N], exist = false;

void dfs (int u) {
    for (auto v: g[u]) {
        if (visited[v]) continue;
        exist = true;
        visited[v] = true;
        dfs(v);
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[v].push_back(u);
    }

    dfs(1);
    if (!exist) visited[1] = true;
    for (int i = 1; i <= n; i++) cout << (visited[i] ? 1 : 0);
    return 0;
}
