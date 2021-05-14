#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, deg[N], a[N];
long long ans[N];
vector <pair <int, int> > g[N];
bool notcyc[N], visited[N], flag = 0;
long long sum = 0, cursum = 0;

void bfs(){
    queue <int> q;
    for (int i = 1; i <= n; i++) if (deg[i] == 1) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto nxt: g[u]) {
            int v = nxt.first, id = nxt.second;
            if (!notcyc[v]) {
                notcyc[u] = true;
                ans[id] = a[u];
                a[u] -= ans[id];
                a[v] -= ans[id];
                deg[v]--;
                if (deg[v] == 1) q.push(v);
            }
        }
    }
}

void dfs (int u, int p, int parity) {
    if (parity) cursum += a[u];
    visited[u] = 1;
    for (auto nxt: g[u]) {
        int v = nxt.first, id = nxt.second;
        if (v == p) continue;
        if (notcyc[v]) continue;
        if (!visited[v]) {
            dfs(v, u, parity ^ 1);
            ans[id] = a[v];
            a[u] -= ans[id];
            a[v] -= ans[id];
        }
        else {
            if (!parity) {
                printf("0");
                exit(0);
            }
            else {
                if (flag) return;
                flag = true;
                ans[id] = cursum - sum;
                a[u] -= ans[id];
                a[v] -= ans[id];
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        deg[u]++; deg[v]++;
    }

    if (n < m) return !printf("0");
    bfs();
    for (int i = 1; i <= n; i++) if (!notcyc[i]) sum += a[i];
    if (sum & 1) return !printf("0");

    sum /= 2;
    for (int i = 1; i <= n; i++) {
        if (!notcyc[i]) {
            dfs(i, i, 1);
            break;
        }
    }

    for (int i = 1; i <= n; i++) if (a[i]) return !printf("0");
    for (int i = 1; i <= m; i++) if (ans[i] < -5e8 || ans[i] > 5e8) return !printf("0");
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i] * 2);
    return 0;
}
