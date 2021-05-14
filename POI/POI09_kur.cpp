#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
const int maxn = 2e3 + 5;

bool dp[N][maxn];
int n, m, k, s, b;
vector <pair <int, int> > g[N];

void dfs (int x, int y) {
    dp[x][y] = true;
    for (auto v: g[x]) {
        if (y >= v.second && !dp[v.first][y - v.second]) dfs(v.first, y - v.second);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    scanf("%d", &k);

    for (int i = 1; i <= k; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(make_pair(v, 0));
    }

    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(make_pair(v, w));
    }

    scanf("%d %d", &s, &b);

    dfs(s, b);

    int ans = 1e9;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= b; j++) {
            if (dp[i][j]) ans = min(ans, j);
        }
    }

    printf("%d", ans);
    return 0;
}

/*
10 2
15
8 2
7 10
8 9
7 2
6 4
5 1
1 3
2 7
2 5
4 10
4 1
2 10
10 2
4 7
5 10
8
9 6 67
7 5 65
2 7 43
6 7 170
4 10 186
6 4 167
4 1 36
1 3 194
5 200
*/
