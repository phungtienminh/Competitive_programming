#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int inf = 1e9 + 7;

int t, n, h, x[N], a[N], b[N];

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
    int S, T, par[N], dist[N], ptr[N];
    bool inqueue[N];
    queue <int> q;

    bool spfa(){
        memset(par, -1, sizeof(par)); memset(dist, 0x3f, sizeof(dist));
        memset(ptr, 0, sizeof(ptr)); memset(inqueue, 0, sizeof(inqueue));
        q.push(S); par[S] = inf; dist[S] = 0; inqueue[S] = true;
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

    void addEdge (int u, int v, int cap, int flow) {
        g[u].push_back(e.size());
        e.push_back(edge(u, v, cap, flow));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, 0));
    }

    long long getFlow(){
        long long ans = 0;
        while (spfa()) while (int cur = dinic(S, inf)) ans += cur;
        return ans;
    }
};

void solve (int Test) {
    scanf("%d %d", &n, &h);
    for (int i = 1; i <= n; i++) scanf("%d %d %d", &x[i], &a[i], &b[i]);
    Flows mf;
    mf.init(0, 2 * n + 1);

    for (int i = 1; i <= n; i++) mf.addEdge(i, i + n, inf, 0);
    for (int i = 1; i <= n; i++) if (a[i] == 0) mf.addEdge(0, i, inf, 0);
    for (int i = 1; i <= n; i++) if (b[i] == h) mf.addEdge(i + n, 2 * n + 1, inf, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            int low = max(a[i], a[j]);
            int high = min(b[i], b[j]);
            if (low <= high) {
                int sum = high - low;
                vector <pair <int, int> > segs;
                for (int k = 1; k <= n; k++) {
                    if (x[k] > min(x[i], x[j]) && x[k] < max(x[i], x[j])) {
                        segs.push_back({a[k], b[k]});
                    }
                }

                sort(segs.begin(), segs.end());
                if (segs.size() > 0) {
                    int l = segs[0].first, r = segs[0].second;
                    for (int i = 1; i < segs.size(); i++) {
                        if (segs[i].first <= r) r = max(r, segs[i].second);
                        else {
                            sum -= max(0, min(r, high) - max(l, low));
                            l = segs[i].first, r = segs[i].second;
                        }
                    }

                    sum -= max(0, min(r, high) - max(l, low));
                }

                mf.addEdge(i + n, j, sum, 0);
            }
        }
    }

    long long res = mf.getFlow();
    printf("Case #%d: ", Test);
    if (res >= 1e9) printf("%d\n", -1);
    else printf("%lld\n", res);
}

int main(){
    //freopen("ladders_and_snakes.txt", "r", stdin);
    //freopen("contestant.out", "w", stdout);
    scanf("%d", &t);
    for (int T = 1; T <= t; T++) solve(T);
    return 0;
}
/*
1
7 30
10 0 10
20 0 10
5 8 21
15 7 20
25 9 22
10 20 30
20 20 30
*/
