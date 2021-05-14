#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int deg_in[N], deg_out[N], n;
bool in[N], visited[N], adj[N][N];
vector <int> all;

void dfs (int u) {
    visited[u] = true;
    all.push_back(u);

    for (int i = 1; i <= 1000; i++) if (adj[u][i] && !visited[i]) dfs(i);
}

void solve(){
    scanf("%d", &n);
    memset(deg_in, 0, sizeof(deg_in));
    memset(deg_out, 0, sizeof(deg_out));
    memset(in, 0, sizeof(in));
    memset(visited, 0, sizeof(visited));

    for (int i = 1; i <= n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        deg_out[u]++;
        deg_in[v]++;
        adj[u][v] = adj[v][u] = true;
        in[u] = in[v] = true;
    }

    int ans = 0;
    for (int i = 1; i <= 1000; i++) {
        if (in[i] && !visited[i]) {
            all.clear();
            dfs(i);

            int res = 0;
            int cur = 0;
            for (auto v: all) {
                res += deg_in[v];
                cur += abs(deg_in[v] - deg_out[v]);
            }

            cur = max(cur, 2);
            ans = ans + res + abs(cur / 2 - 1) + 1;
        }
    }

    printf("%d", ans);
}

int main(){
    solve();
    return 0;
}
