#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, deg[N];
vector <int> g[N];
bool visited[N];

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        deg[i] += x;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u); deg[u]--; deg[v]--;
    }

    queue <int> q;
    for (int i = 1; i <= n; i++) if (deg[i] >= 0) q.push(i);
    vector <pair <int, int> > ans;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited[u] = true;
        for (auto v: g[u]) {
            if (visited[v]) continue;
            ans.push_back({u, v});
            deg[v]++;
            if (deg[v] == 0) q.push(v);
        }
    }

    if (ans.size() != m) printf("IMPOSSIBLE");
    else for (int i = 0; i < m; i++) printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
