#include <bits/stdc++.h>

using namespace std;

const int N = 5005;
const int inf = 1e9 + 2277;

int n, deg[N], par[N], dp[N], flow[N], totdeg[N];
vector <int> g[N], g2[N];
vector <vector <int> > c, f;
bool visited[N];

int get_pos (int u, int v) {
    for (int i = 0; i < g[u].size(); i++) if (g[u][i] == v) return i;
}

bool bfs(){
    queue <int> q;
    memset(par, 0, sizeof(par));
    par[1] = -1; q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        assert(u != 0);
        if (u == n) return true;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (!par[v] && f[u][i] < c[u][i]) {
                par[v] = u;
                q.push(v);
            }
        }
    }

    return 0;
}

void edmond_karp(){
    int delta = inf;
    for (int u = n; par[u] != -1; u = par[u]) delta = min(delta, c[par[u]][get_pos(par[u], u)] - f[par[u]][get_pos(par[u], u)]), assert(par[u] != 0), assert(u != 0);
    for (int u = n; u != 1; u = par[u]) {
        assert(par[u] != 0); assert(u != 0);
        f[par[u]][get_pos(par[u], u)] += delta;
        f[u][get_pos(u, par[u])] -= delta;
    }
}

void redfs (int u) {
    assert(u != 0);
    visited[u] = true;
    for (auto v: g2[u]) {
        if (!visited[v]) {
            redfs(v);
            dp[u] += dp[v];
            c[u][get_pos(u, v)] = dp[v];
        }
        else {
            dp[u]++;
            c[u][get_pos(u, v)] = 1;
        }
    }
}

void rebfs(){
    queue <int> q; q.push(1); flow[1] = dp[1];
    while (!q.empty()) {
        int u = q.front(); q.pop();
        assert(u != 0);
        if (u == n) return;
        int curflow = flow[u];
        for (int i = 1; i < g2[u].size(); i++) {
            int v = g2[u][i], curpos = get_pos(u, v);
            flow[v] += c[u][curpos];
            curflow -= c[u][curpos];
            c[u][curpos]--;
            if (--deg[v] == 0) q.push(v);
        }

        int v = g2[u][0], curpos = get_pos(u, v);
        flow[v] += curflow;
        c[u][curpos] = curflow - 1;
        if (--deg[v] == 0) q.push(v);
    }
}

int main(){
    scanf("%d", &n); c.resize(n + 1); f.resize(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int num;
        scanf("%d", &num);
        //c[i].resize(num); f[i].resize(num);
        for (int j = 0; j < num; j++) {
            int v;
            scanf("%d", &v);
            g2[i].push_back(v);
            ++deg[v]; totdeg[i]++; totdeg[v]++;
            g[i].push_back(v); g[v].push_back(i);
        }
    }

    //for (int i = 0; i <= n; i++) c[i].resize(20), f[i].resize(20);
    for (int i = 1; i <= n; i++) c[i].resize(totdeg[i]), f[i].resize(totdeg[i]);
    visited[n] = true; dp[n] = 1;
    redfs(1); rebfs();
    //for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    //cout << "\n";
    while (bfs()) edmond_karp();
    for (int i = 0; i < g[1].size(); i++) flow[1] -= f[1][i];
    printf("%d", flow[1]);
    return 0;
}
