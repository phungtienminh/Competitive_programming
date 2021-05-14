#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

vector <int> g[N];
int color[N], n, m;
bool visited[N];

void input(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

void dfs (int u, int c) {
    if (color[u]) return;
    color[u] = c;
    for (int v: g[u]) dfs(v, 3 - c);
}

void solve(){
    memset(color, 0, sizeof(color));
    for (int i = 1; i <= n; i++) {
        if (g[i].size() == 0) {
            puts("NIE");
            return;
        }
    }

    for (int i = 1; i <= n; i++) if (!color[i]) dfs(i, 1);

    puts("TAK");
    for (int i = 1; i <= n; i++) puts(color[i] == 1 ? "K" : "S");
}

int main(){
    input();
    solve();
    return 0;
}
