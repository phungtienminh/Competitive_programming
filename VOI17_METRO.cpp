#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;

class Edges {
public:
    int w, to, id;

    Edges (int w, int to, int id) {
        this->w = w;
        this->to = to;
        this->id = id;
    }
};

class Node {
public:
    int dist, idx, last;

    Node (int dist, int idx, int last) {
        this->dist = dist;
        this->idx = idx;
        this->last = last;
    }

    bool operator<(const Node &other) const {
        return dist > other.dist;
    }
};

vector <Edges> g[N];
int n, m, s, t, coeff, dist[N];
map <int, int> mm[N];

void fropen(){
    freopen("METRO.INP", "r", stdin);
    freopen("METRO.out", "w", stdout);
}

void input(){
    scanf("%lld %lld %lld %lld %lld", &n, &m, &s, &t, &coeff);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        g[u].push_back(Edges(w, v, i));
    }
}

void dijkstra(){
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0; pq.push(make_pair(dist[s], s));

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d == dist[u]) {
            for (auto v: g[u]) {
                if (dist[v.to] > dist[u] + v.w + (u != s ? v.id : 0)) {
                    dist[v.to] = dist[u] + v.w + (u != s ? v.id : 0);
                    pq.push(make_pair(dist[v.to], v.to));
                }
            }
        }
    }

    if (dist[t] > 1e18) printf("-1");
    else printf("%lld", dist[t]);
}

void dijkstra2(){
    priority_queue <Node, vector <Node> > pq;
    mm[s][0] = 0; pq.push(Node(mm[s][0], s, 0));

    while (!pq.empty()) {
        Node nd = pq.top(); pq.pop();
        int d = nd.dist;
        int u = nd.idx;
        int last = nd.last;

        if (d == mm[u][last]) {
            for (auto v: g[u]) {
                if (!mm[v.to].count(v.id) || mm[v.to][v.id] > mm[u][last] + v.w + (u != s ? v.id + last * coeff : 0)) {
                    mm[v.to][v.id] = mm[u][last] + v.w + (u != s ? v.id + last * coeff : 0);
                    pq.push(Node(mm[v.to][v.id], v.to, v.id));
                }
            }
        }
    }

    int ans = 1e18 + 500;
    for (auto i: mm[t]) ans = min(ans, i.second);

    if (ans > 1e18) printf("-1");
    else printf("%lld", ans);
}

void solve(){
    if (coeff == 0) dijkstra();
    else dijkstra2();
}

signed main(){
    fropen();
    input();
    solve();
    return 0;
}
