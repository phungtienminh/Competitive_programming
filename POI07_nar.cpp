#include <bits/stdc++.h>

using namespace std;

const int N = 10005;
const int inf = 1e9 + 2277;

class Flows {
private:
    struct edge {
        int from, to, cap, flow;

        edge (int from = 0, int to = 0, int cap = 0, int flow = 0) {
            this->from = from;
            this->to = to;
            this->cap = cap;
            this->flow = flow;
        }

        int other (edge ed, int u) {
            return (ed.from == u ? ed.to : ed.from);
        }
    } E;

    int S, T, dist[N], par[N], ptr[N];
    vector <edge> e;
    vector <int> g[N];
    queue <int> q;

    bool bfs() {
        for (int i = 0; i < N; i++) {
            par[i] = -1;
            dist[i] = inf;
            ptr[i] = 0;
        }

        dist[S] = 0; par[S] = inf; q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < g[u].size(); i++) {
                int V = g[u][i];
                edge ed = e[V];
                int v = E.other(ed, u);

                if (dist[v] > dist[u] + 1 && ed.flow < ed.cap) {
                    dist[v] = dist[u] + 1;
                    par[v] = V;
                    q.push(v);
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
        S = _S;
        T = _T;
    }

    void addEdge (int u, int v, int cap, int flow) {
        g[u].push_back(e.size());
        e.push_back(edge(u, v, cap, flow));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, 0));
    }

    int solve() {
        int maxflow = 0;
        while (bfs()) while (int cur = dinic(S, inf)) maxflow += cur;

        return maxflow;
    }
} mf;

int main(){
    int n;
    scanf("%d", &n);
    bool exist = false;
    mf.init(1, 2 * n);

    mf.addEdge(1, 2, inf, 0);
    mf.addEdge(2 * n - 1, 2 * n, inf, 0);
    for (int i = 1; i <= n - 1; i++) {
        int num; scanf("%d", &num);
        for (int j = 0; j < num; j++) {
            int x; scanf("%d", &x);
            if (x == n && i == 1) exist = true;
            else mf.addEdge(i * 2, x * 2 - 1, inf, 0);
        }
    }

    for (int i = 2; i <= n - 1; i++) mf.addEdge(i * 2 - 1, i * 2, 1, 0);

    int res = mf.solve();
    printf("%d", res + exist);
    return 0;
}
