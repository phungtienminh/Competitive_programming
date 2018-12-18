#include <bits/stdc++.h>

using namespace std;

class Edges {
public:
    int to, cost, type;

    Edges (int to, int cost, int type) {
        this->to = to;
        this->cost = cost;
        this->type = type;
    }
};

vector <Edges> g[105];

void dijkstra (int s, int f) {
    int dist[105];
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    pq.push(make_pair(dist[s], s));

    while (!pq.empty()) {
        pair <int, int> onTop = pq.top(); pq.pop();

        int d = onTop.first;
        int u = onTop.second;

        if (d == dist[u]) {
            for (int i = 0; i<g[u].size(); i++) {
                Edges v = g[u][i];
                if (v.type == 1) {
                    if (dist[v.to] > dist[u] + v.cost) {
                        dist[v.to] = dist[u] + v.cost;
                        pq.push(make_pair(dist[v.to], v.to));
                    }
                }
                else {
                    if (dist[v.to] > dist[u]/2) {
                        dist[v.to] = dist[u]/2;
                        pq.push(make_pair(dist[v.to], v.to));
                    }
                }
            }
        }
    }
    printf("%d", dist[f]);
}

int main(){
    int n, s, f, m, u, v, w, q;
    scanf("%d", &n);
    scanf("%d %d", &s, &f);
    scanf("%d", &m);

    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(Edges(v, w, 1));
    }
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d", &u, &v);
        g[u].push_back(Edges(v, 0, 2));
    }
    dijkstra(s, f);
    return 0;
}
