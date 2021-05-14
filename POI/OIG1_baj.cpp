#include <bits/stdc++.h>

using namespace std;

const int N = 7e3 + 5;
const int maxn = 3e5 + 5;

struct disj {
    int par[N];

    void init (int n) {
        for (int i = 1; i <= n; i++) par[i] = i;
    }

    int Find (int x) {
        return par[x] == x ? x : par[x] = Find(par[x]);
    }

    bool same (int x, int y) {
        return Find(x) == Find(y);
    }

    void join (int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;

        par[y] = x;
    }
} dsu;

class Edges {
public:
    int u, v, w, id;

    Edges (int u, int v, int w, int id): u(u), v(v), w(w), id(id) {}
    bool operator < (const Edges &other) const {
        return w < other.w;
    }
};

int n, m;
vector <Edges> edge;
bool ans[maxn];

void buildMST () {
    int r = 0;
    for (int i = 0; i < edge.size(); i = r) {
        int cur = edge[i].w;
        while (r < edge.size() && edge[r].w == cur) r++;

        for (int j = i; j < r; j++) {
            if (!dsu.same(edge[j].u, edge[j].v)) ans[edge[j].id] = true;
            else ans[edge[j].id] = false;
        }

        for (int j = i; j < r; j++) {
            if (dsu.same(edge[j].u, edge[j].v)) continue;

            dsu.join(edge[j].u, edge[j].v);
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edge.push_back(Edges(u, v, w, i));
    }

    sort(edge.begin(), edge.end());
    dsu.init(n);
    buildMST();

    for (int i = 1; i <= m; i++) puts(ans[i] ? "TAK" : "NIE");
    return 0;
}
