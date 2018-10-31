#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, m, a[N], sum = 0;

class Flows {
private:
    struct edge {
        int u, v, cap, flow;
        edge (int u = 0, int v = 0, int cap = 0, int flow = 0): u(u), v(v), cap(cap), flow(flow) {}
        int other (edge ed, int u) {
            return ed.u == u ? ed.v : ed.u;
        }
    } E;

    vector <int> g[N];
    vector <edge> e;
    int S, T, dist[N], par[N], ptr[N];
    queue <int> q;
    bool inqueue[N];

    bool spfa(){
        memset(dist, 0x3f, sizeof(dist)); memset(par, -1, sizeof(par)); memset(inqueue, 0, sizeof(inqueue)); memset(ptr, 0, sizeof(ptr));
        q.push(S); dist[S] = 0; par[S] = 1e9; inqueue[S] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop(); inqueue[u] = false;
            for (auto V: g[u]) {
                edge ed = e[V];
                int v = E.other(ed, u);
                if (dist[v] > dist[u] + 1 && ed.flow < ed.cap) {
                    dist[v] = dist[u] + 1;
                    par[v] = V;
                    if (!inqueue[v]) {
                        inqueue[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        return par[T] != -1;
    }

    int dinic (int u, int flow) {
        if (u == T || !flow) return flow;
        for (int &i = ptr[u]; i < g[u].size(); i++) {
            int V = g[u][i];
            edge ed = e[V];
            int v = E.other(ed, u);
            if (dist[v] == dist[u] + 1 && ed.flow < ed.cap) {
                int delta = dinic(v, min(flow, ed.cap - ed.flow));
                if (delta > 0) {
                    e[V].flow += delta;
                    e[V ^ 1].flow -= delta;
                    return delta;
                }
            }
        }

        return 0;
    }

public:
    void init (int _S, int _T) {
        S = _S; T = _T;
    }

    void reset(){
        for (int i = 0; i < N; i++) g[i].clear();
        e.clear();
    }

    void addEdge (int u, int v, int cap, int flow) {
        g[u].push_back(e.size());
        e.push_back(edge(u, v, cap, flow));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, 0));
    }

    int solve(){
        int flow = 0;
        while (spfa()) while (int cur = dinic(S, 1e9)) flow += cur;
        return flow;
    }
} mcmf;

int main(){
    scanf("%d", &n); mcmf.init(0, n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += (a[i] > 0 ? a[i] : 0);

        if (a[i] > 0) mcmf.addEdge(0, i, a[i], 0);
        else mcmf.addEdge(i, n + 1, -a[i], 0);
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        mcmf.addEdge(u, v, 1e9, 0);
    }

    printf("%d", sum - mcmf.solve());
    return 0;
}
