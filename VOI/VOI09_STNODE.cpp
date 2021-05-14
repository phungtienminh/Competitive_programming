#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int cnt = 0, d[N], par[N], in[N], n, m, s, t;
bool visited[N];
vector <int> g[N], path;

void bfs() {
    queue <int> q; memset(d, 0x3f, sizeof(d));
    q.push(s); d[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }

    if (d[t] > 1e9) {
        printf("0");
        exit(0);
    }

    int cur = t;
    while (cur != s) {
        cur = par[cur];
        path.push_back(cur);
    }

    reverse(path.begin(), path.end()); path.push_back(t);
    for (auto i: path) in[i] = ++cnt;
}

int rebfs (int s) {
    visited[s] = true;
    queue <int> q; q.push(s);
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (!visited[v] && !in[v]) {
                visited[v] = true;
                q.push(v);
            }
            else ans = max(ans, in[v]);
        }
    }

    return ans;
}

int main(){
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
    }

    bfs();
    int ptr = 0, ans = 0;
    for (auto i: path) {
        if (i != s && i != t && ptr <= in[i]) ans++;
        ptr = max(ptr, rebfs(i));
    }

    printf("%d", ans);
    return 0;
}
