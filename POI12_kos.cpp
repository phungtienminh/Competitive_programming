#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 5;

int n, m, u[N], v[N], res[N], deg[N];

class Flows {
private:
    struct edge {
        int u, v, cap, flow;
        edge (int u = 0, int v = 0, int cap = 0, int flow = 0): u(u), v(v), cap(cap), flow(flow) {}
        int other (edge e, int u) {
            return e.u == u ? e.v : e.u;
        }
    } E;

    vector <int> g[N];
    vector <edge> e;
    int S, T, par[N], dist[N], ptr[N];
    queue <int> q;
    bool inqueue[N];

    bool bfs(){
        memset(par, -1, sizeof(par)); memset(dist, 0x3f, sizeof(dist)); memset(ptr, 0, sizeof(ptr)); memset(inqueue, 0, sizeof(inqueue));
        q.push(S); par[S] = 1e9 + 2277; dist[S] = 0; inqueue[S] = true;
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
    void reset(){
        e.clear();
        for (int i = 0; i < N; i++) g[i].clear();
    }

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

    int getFlow (int type) {
        int ans = 0;
        while (bfs()) while (int cur = dinic(S, (int)1e9 + 2277)) ans += cur;
        if (type) for (auto i: e) if (i.flow > 0 && i.u >= 1 && i.u <= n) res[i.v - n] = (i.u == u[i.v - n] ? 1 : 0);
        return ans;
    }
} mf;

bool check (int mid, int type) {
    mf.reset(); mf.init(0, n + m + 1);
    for (int i = 1; i <= n; i++) mf.addEdge(0, i, mid, 0);
    for (int i = 1; i <= m; i++) {
        mf.addEdge(u[i], i + n, 1, 0);
        mf.addEdge(v[i], i + n, 1, 0);
        mf.addEdge(i + n, n + m + 1, 1, 0);
    }

    //if (mid == 1) cout << mf.getFlow() << " flows \n";
    return mf.getFlow(type) == m;
}

int readInt(){
    int ans = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int main(){
    n = readInt(); m = readInt();
    for (int i = 1; i <= m; i++) u[i] = readInt(), v[i] = readInt(), deg[u[i]]++, deg[v[i]]++;

    int l = 0, r = *max_element(deg + 1, deg + n + 1);
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid, 0)) r = mid - 1;
        else l = mid + 1;
    }

    check(l, 1);
    printf("%d\n", l);
    for (int i = 1; i <= m; i++) printf("%d\n", res[i]);
    return 0;
}
/*
5 20
1 2
2 1
1 3
3 1
1 4
4 1
1 5
5 1
1 2
2 1
1 3
3 1
1 4
4 1
1 5
5 1
2 3
5 4
5 2
4 3
*/
