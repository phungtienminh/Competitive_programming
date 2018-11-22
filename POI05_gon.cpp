#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int n, m, a, b, d[N], d2[N], deg[N], Deg[N], cnt = 0;
vector <int> g[N];
bool visited[N];

void prebfs(){
    queue <int> q;
    for (int i = 1; i <= n; i++) if (Deg[i] == 1) q.push(i), visited[i] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (visited[v]) continue;
            if (--Deg[v] == 1) visited[v] = true, q.push(v);
        }
    }
}

void bfs (int s, int type) {
    queue <int> q; q.push(s);
    if (type == 1) {
        memset(d, 0x3f, sizeof(d)); d[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v: g[u]) {
                if (d[v] > d[u] + 1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    else {
        memset(d2, 0x3f, sizeof(d2)); d2[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v: g[u]) {
                if (d2[v] > d2[u] + 1) {
                    d2[v] = d2[u] + 1;
                    q.push(v);
                }
            }
        }
    }
}

int main(){
    scanf("%d %d %d %d", &n, &m, &a, &b);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
        ++deg[u]; ++deg[v]; ++Deg[u]; ++Deg[v];
    }

    prebfs();
    bfs(b, 1); bfs(a, 2);

    int ans = 0;
    for (int i = 1; i <= n; i++) if (d2[i] < d[i] && !visited[i]) return !printf("NIE");
    for (int i = 1; i <= n; i++) if (d2[i] <= d[i] && deg[i] == 1) ans = max(ans, d[i]);
    printf("%d", ans);
    return 0;
}
/*
8 8 6 5
1 2
1 3
3 4
4 2
5 4
1 6
6 7
7 8
*/
