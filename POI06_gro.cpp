#include <bits/stdc++.h>

using namespace std;

const int N = 205;
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

        int other (edge e, int u) {
            return (e.from == u ? e.to : e.from);
        }
    } E;

    vector <edge> e;
    vector <int> g[N];
    int dist[N], par[N], ptr[N];
    queue <int> q;
    int S, T;

    bool bfs() {
        for (int i = 0; i < N; i++) {
            dist[i] = inf;
            par[i] = -1;
            ptr[i] = 0;
        }

        q.push(S); dist[S] = 0; par[S] = inf;
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

    int solve(){
        int maxflow = 0;
        while (bfs()) while (int cur = dinic(S, inf)) maxflow += cur;

        return maxflow;
    }
} mf;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    mf.init(1, n);

    int num; cin >> num;
    for (int i = 0; i < num; i++) {
        int x; cin >> x;
        mf.addEdge(1, x, 1, 0);
    }

    for (int i = 2; i <= n - 1; i++) {
        cin >> num;
        for (int j = 0; j < num; j++) {
            int x; cin >> x;

            if (x == n) mf.addEdge(i, x, 1, 0);
            else mf.addEdge(i, x, inf, 0);
        }
    }

    cout << mf.solve();
    return 0;
}
