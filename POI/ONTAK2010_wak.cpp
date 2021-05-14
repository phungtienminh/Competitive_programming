#include <bits/stdc++.h>

using namespace std;

const int N = 605;
const int inf = 1e9 + 2277;

int n, a[N], k;

class Flows {
private:
    struct edge {
        int u, v, cap, flow, cost;

        edge (int u = 0, int v = 0, int cap = 0, int flow = 0, int cost = 0): u(u), v(v), cap(cap), flow(flow), cost(cost) {}

        int other (edge e, int u) {
            return e.u == u ? e.v : e.u;
        }
    } E;

    int par[N], dist[N], S, T;
    queue <int> q;
    vector <edge> e;
    vector <int> g[N];
    bool inqueue[N];

    bool SPFA(){
        memset(dist, 0x3f, sizeof(dist));
        memset(par, -1, sizeof(par));
        memset(inqueue, 0, sizeof(inqueue));

        dist[S] = 0; par[S] = inf; inqueue[S] = true;
        q.push(S);

        while (!q.empty()) {
            int u = q.front(); q.pop(); inqueue[u] = false;
            for (int V: g[u]) {
                edge ed = e[V];
                int v = E.other(ed, u);

                if (dist[v] > dist[u] + ed.cost && ed.flow < ed.cap) {
                    dist[v] = dist[u] + ed.cost;
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

    int edmond_karp(){
        int delta = inf;
        int u = T;

        while (u != S) {
            delta = min(delta, e[par[u]].cap - e[par[u]].flow);
            u = E.other(e[par[u]], u);
        }

        u = T;
        while (u != S) {
            e[par[u]].flow += delta;
            e[par[u] ^ 1].flow -= delta;
            u = E.other(e[par[u]], u);
        }

        return delta;
    }

public:
    void init (int _S, int _T) {
        S = _S;
        T = _T;
    }

    void addEdge (int u, int v, int cap, int flow, int cost) {
        g[u].push_back(e.size());
        e.push_back(edge(u, v, cap, flow, cost));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, 0, -cost));
    }

    int solve(){
        int mincost = 0;
        while (SPFA()) edmond_karp();
        for (auto i: e) if (i.flow > 0) mincost += i.flow * i.cost;

        return mincost;
    }
} mcmf;

int main(){
    scanf("%d %d", &n, &k);
    mcmf.init(0, 3 * n + 1);
    for (int i = 0; i < 3 * n; i++) {
        scanf("%d", &a[i]);
        mcmf.addEdge(i, min(i + n, 3 * n), 1, 0, -a[i]);
        mcmf.addEdge(i, i + 1, k, 0, 0);
    }

    mcmf.addEdge(3 * n, 3 * n + 1, k, 0, 0);
    printf("%d", -mcmf.solve());
    return 0;
}
