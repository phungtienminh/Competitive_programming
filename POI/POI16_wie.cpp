#include <bits/stdc++.h>

using namespace std;

const int N = 205;
const int maxn = 1 << 13;

class Edges {
public:
    int to, w, mask;

    Edges (int to, int w, int mask) {
        this->to = to;
        this->w = w;
        this->mask = mask;
    }
};

class Node {
public:
    int dist, idx, mask;

    Node (int dist, int idx, int mask) {
        this->dist = dist;
        this->idx = idx;
        this->mask = mask;
    }

    bool operator<(const Node &other) const {
        return dist > other.dist;
    }
};

int dp[N][maxn], mask_city[N], n, m, p, k;
vector <Edges> g[N];

void dijkstra (int s) {
    memset(dp, 0x3f, sizeof(dp));
    dp[s][mask_city[s]] = 0;
    priority_queue <Node, vector <Node> > pq;
    pq.push(Node(dp[s][mask_city[s]], s, mask_city[s]));

    while (!pq.empty()) {
        Node topval = pq.top(); pq.pop();
        int d = topval.dist;
        int u = topval.idx;
        int mask = topval.mask;

        if (d == dp[u][mask]) {
            for (int i = 0; i < g[u].size(); i++) {
                int v = g[u][i].to;
                int w = g[u][i].w;
                int mask_road = g[u][i].mask;

                if (dp[v][mask | mask_city[v]] > dp[u][mask] + w && ((mask & mask_road) == mask_road)) {
                    dp[v][mask | mask_city[v]] = dp[u][mask] + w;
                    pq.push(Node(dp[v][mask | mask_city[v]], v, mask | mask_city[v]));
                }
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int i = 0; i < maxn; i++) ans = min(ans, dp[n][i]);
    if (ans > 1e9) printf("-1\n");
    else printf("%d\n", ans);
}

int main(){
    memset(mask_city, 0, sizeof(mask_city));
    scanf("%d %d %d %d", &n, &m, &p, &k);

    for (int i = 0; i < k; i++) {
        int id, num;
        scanf("%d %d", &id, &num);
        for (int j = 0; j < num; j++) {
            int monster;
            scanf("%d", &monster);
            --monster;
            mask_city[id] |= (1 << monster);
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w, num;
        int mask = 0;
        scanf("%d %d %d %d", &u, &v, &w, &num);
        for (int j = 0; j < num; j++) {
            int monster;
            scanf("%d", &monster);
            --monster;
            mask |= (1 << monster);
        }

        g[u].push_back(Edges(v, w, mask));
        g[v].push_back(Edges(u, w, mask));
    }

    dijkstra(1);
    return 0;
}
