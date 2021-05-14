#include <bits/stdc++.h>

using namespace std;

const int N = 205;

class Flows {
private:
    struct edge {
        int u, v, cap, flow, cost;

        edge (int u = 0, int v = 0, int cap = 0, int flow = 0, int cost = 0) {
            this->u = u;
            this->v = v;
            this->cap = cap;
            this->flow = flow;
            this->cost = cost;
        }

        int other (edge ed, int u) {
            return ed.u == u ? ed.v : ed.u;
        }
    } E;

    vector <edge> e;
    vector <int> g[2 * N];
    int par[2 * N], dist[2 * N], S, T;
    bool inqueue[2 * N];
    queue <int> q;

    bool SPFA(){
        memset(dist, 0x3f, sizeof(dist));
        memset(par, -1, sizeof(par));
        memset(inqueue, 0, sizeof(inqueue));

        inqueue[S] = true; par[S] = 1e9; dist[S] = 0; q.push(S);
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
        int delta = 1e9;
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

    pair <int, int> flow(){
        int maxflow = 0;
        int mincost = 0;

        while (SPFA()) maxflow += edmond_karp();
        for (auto i: e) if (i.flow > 0) mincost += i.flow * i.cost;

        return make_pair(mincost, maxflow);
    }
} mcmf;

int n;

void input(){
    scanf("%d", &n);
}

void solve(){
    mcmf.init(0, 2 * n + 1);
    for (int i = 1; i <= n; i++) {
        int m, a, b, k;
        scanf("%d %d %d %d", &m, &a, &b, &k);
        for (int j = a; j <= b; j++) mcmf.addEdge(i, j + n, 1, 0, k * abs(m - j));
    }

    for (int i = 1; i <= n; i++) {
        mcmf.addEdge(0, i, 1, 0, 0);
        mcmf.addEdge(i + n, 2 * n + 1, 1, 0, 0);
    }

    pair <int, int> ans = mcmf.flow();
    if (ans.second < n) printf("NIE");
    else printf("%d", ans.first);
}

int main(){
    input();
    solve();
    return 0;
}
