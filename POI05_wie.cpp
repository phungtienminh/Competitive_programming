#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

vector <int> g[N], edge[N][N];
int n, h[N], ans = 0, dist[N];

void dfs (int u, int p) {
    int Max1 = 0, Max2 = 0;
    for (auto v: g[u]) {
        if (v == p) continue;
        h[v] = h[u] + 1;
        dfs(v, u);
        dist[u] = max(dist[u], dist[v] + 1);
        if (dist[v] + 1 > Max1) {
            Max2 = Max1;
            Max1 = dist[v] + 1;
        }
        else if (dist[v] + 1 > Max2) Max2 = dist[v] + 1;
    }

    ans = max(ans, Max1 + Max2 + h[u]);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n - 2; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edge[min(u, v)][max(u, v)].push_back(i);
        edge[min(u, w)][max(u, w)].push_back(i);
        edge[min(v, w)][max(v, w)].push_back(i);
    }

    for (int i = 0; i <= n - 1; i++) {
        for (int j = i + 1; j <= n - 1; j++) {
            if (edge[i][j].size() == 2) {
                g[edge[i][j][0]].push_back(edge[i][j][1]);
                g[edge[i][j][1]].push_back(edge[i][j][0]);
            }
        }
    }

    for (int i = 1; i <= n - 2; i++) {
        memset(h, 0, sizeof(h)); memset(dist, 0, sizeof(dist));
        dfs(i, i);
    }

    printf("%d", ++ans);
    return 0;
}
