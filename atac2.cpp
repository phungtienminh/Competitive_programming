#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
const int maxn = 150;
const int inf = 1e9 + 2277;

int n, m, k, x, d[maxn / 2][maxn / 2], dist[N], a[N], ptr = 0, b[N];
vector <int> adj[N];
bool used[N];

class Flows {
private:
    struct edge {
        int u, v, cap, flow, cost;
        edge (int u = 0, int v = 0, int cap = 0, int flow = 0, int cost = 0): u(u), v(v), cap(cap), flow(flow), cost(cost) {}
        int other (edge ed, int u) {
            return ed.u == u ? ed.v : ed.u;
        }
    } E;

    vector <edge> e;
    vector <int> g[maxn];
    queue <int> q;
    int dis[maxn], par[maxn], S, T;
    bool inqueue[maxn];

    bool spfa(){
        memset(dis, 0x3f, sizeof(dis)); memset(par, -1, sizeof(par)); memset(inqueue, 0, sizeof(inqueue));
        dis[S] = 0; par[S] = inf; inqueue[S] = true; q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop(); inqueue[u] = false;
            for (auto V: g[u]) {
                edge ed = e[V];
                int v = E.other(ed, u);
                if (dis[v] > dis[u] + ed.cost && ed.flow < ed.cap) {
                    dis[v] = dis[u] + ed.cost;
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
        int u = T, delta = inf;
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
        S = _S; T = _T;
    }

    void addEdge (int u, int v, int cap, int flow, int cost) {
        g[u].push_back(e.size());
        e.push_back(edge(u, v, cap, flow, cost));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, 0, -cost));
    }

    int getFlow(){
        int mincost = 0;
        while (spfa()) edmond_karp();
        for (auto i: e) if (i.flow > 0) mincost += i.flow * i.cost;
        return mincost;
    }
} mcmf;

int main(){
    #ifndef Futymy
        freopen("atac2.in", "r", stdin);
        freopen("atac2.out", "w", stdout);
    #endif // Futymy
    scanf("%d %d %d %d", &n, &m, &k, &x);
    for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v); adj[v].push_back(u);
    }

    for (auto i: adj[x]) if (!used[i]) used[i] = true, b[++ptr] = i;
    for (int i = 1; i <= k; i++) {
        queue <int> q;
        memset(dist, 0x3f, sizeof(dist)); dist[a[i]] = 0;
        q.push(a[i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v: adj[u]) {
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        for (int j = 1; j <= ptr; j++) d[i][j] = dist[b[j]];
    }

    mcmf.init(0, k + ptr + 1);
    for (int i = 1; i <= k; i++) mcmf.addEdge(0, i, 1, 0, 0);
    for (int i = 1; i <= ptr; i++) mcmf.addEdge(k + i, k + ptr + 1, 1, 0, 0);
    for (int i = 1; i <= k; i++) for (int j = 1; j <= ptr; j++) mcmf.addEdge(i, j + k, 1, 0, d[i][j]);
    printf("%d", mcmf.getFlow());
    return 0;
}
