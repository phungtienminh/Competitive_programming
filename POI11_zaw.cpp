#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

struct edge {
    int v, w, id;
    edge (int v = 0, int w = 0, int id = 0): v(v), w(w), id(id) {}
};

int t, n, m, d[N];
vector <edge> g[N];

int readInt(){
    int ans = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + c - '0';
    }
}

int main(){
    n = readInt(); m = readInt();
    for (int i = 1; i <= m; i++) {
        int u, v, w1, w2;
        u = readInt(); v = readInt(); w1 = readInt(); w2 = readInt();
        g[u].push_back(edge(v, w1, i));
        g[v].push_back(edge(u, w2, i));
    }

    int cur = 2e9;
    for (auto j: g[1]) {
        if (j.w >= cur) continue;
        memset(d, 0x3f, sizeof(d)); d[j.v] = 0;
        priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
        pq.push({d[j.v], j.v});
        while (!pq.empty()) {
            int dist = pq.top().first, u = pq.top().second; pq.pop();
            if (dist > cur - j.w) break;
            if (u == 1) break;
            if (dist == d[u]) {
                for (auto v: g[u]) {
                    if (v.id == j.id) continue;
                    if (d[v.v] > d[u] + v.w && d[u] + v.w < cur) {
                        d[v.v] = d[u] + v.w;
                        pq.push({d[v.v], v.v});
                    }
                }
            }
        }

        cur = min(cur, d[1] + j.w);
        //cout << ++cnt << "\n";
    }

    printf("%d", cur);
    return 0;
}
