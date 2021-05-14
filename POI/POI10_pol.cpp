#include <bits/stdc++.h>

using namespace std;

const int N = 105;

vector <pair <int, int> > g[N];
priority_queue <int> d[N][N];
int ans[N][N][N], n, m, q;

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({w, v});
    }

    memset(ans, -1, sizeof(ans));
    for (int i = 1; i <= n; i++) {
        priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
        pq.push({0, i});
        while (!pq.empty()) {
            int dist = pq.top().first, u = pq.top().second; pq.pop();
            if (!d[i][u].empty() && d[i][u].top() < dist) continue;
            for (auto v: g[u]) {
                if (d[i][v.second].size() < 100 || d[i][v.second].top() > v.first + dist) {
                    d[i][v.second].push(v.first + dist);
                    pq.push({v.first + dist, v.second});
                    if (d[i][v.second].size() > 100) d[i][v.second].pop();
                }
            }
        }

        for (int j = 1; j <= n; j++) {
            while (!d[i][j].empty()) {
                ans[i][j][d[i][j].size()] = d[i][j].top();
                d[i][j].pop();
            }
        }
    }

    scanf("%d", &q);
    while (q--) {
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        printf("%d\n", ans[u][v][k]);
    }
    return 0;
}
