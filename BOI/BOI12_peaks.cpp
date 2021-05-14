#include <bits/stdc++.h>

using namespace std;

const int N = 2005;
const int maxn = 1e5 + 5;

int n, m, a[N][N], l[maxn], r[maxn];
bool visited[maxn], f = false;
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool inside (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int enc (int x, int y) {
    return (x - 1) * m + y;
}

int dec (int cell) {
    int row = (cell % m == 0 ? cell / m : cell / m + 1);
    int col = (cell % m == 0 ? m : cell % m);
    return a[row][col];
}

struct disj {
    int par[maxn], Max[maxn];
    bool ispeak[maxn];

    void init (int n) {
        for (int i = 1; i <= n; i++) par[i] = i, ispeak[i] = false, Max[i] = dec(i);
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
        if (ispeak[y] && !ispeak[x]) swap(x, y);
        par[y] = x;
        Max[x] = max(Max[x], Max[y]);
    }
} dsu;

void bfs (int x, int y) {
    queue <pair <int, int> > q; q.push({x, y}); visited[enc(x, y)] = true;
    f = true;

    while (!q.empty()) {
        pair <int, int> val = q.front(); q.pop();
        for (int i = 0; i < 8; i++) {
            if (inside(val.first + dx[i], val.second + dy[i])) {
                if (a[val.first + dx[i]][val.second + dy[i]] == a[val.first][val.second] && !visited[enc(val.first + dx[i], val.second + dy[i])]) {
                    dsu.join(enc(val.first, val.second), enc(val.first + dx[i], val.second + dy[i]));
                    q.push({val.first + dx[i], val.second + dy[i]});
                    visited[enc(val.first + dx[i], val.second + dy[i])] = true;
                }
                else if (a[val.first + dx[i]][val.second + dy[i]] > a[val.first][val.second]) f = false;
            }
        }
    }
}

int main(){
    //freopen("test.inp", "r", stdin);
    //freopen("test.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    dsu.init(n * m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dsu.Find(enc(i, j)) != enc(i, j)) continue;
            bfs(i, j);
            if (f) dsu.ispeak[enc(i, j)] = true;
        }
    }

    vector <pair <int, pair <int, int> > > peak, vec;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dsu.Find(enc(i, j)) == enc(i, j) && dsu.ispeak[enc(i, j)]) peak.push_back({a[i][j], {i, j}});
            vec.push_back({a[i][j], {i, j}});
        }
    }

    int Max = 0;
    for (auto i: peak) Max = max(Max, i.first);
    for (int i = 1; i <= peak.size(); i++) {
        l[i] = 1, r[i] = peak[i - 1].first;
        if (peak[i - 1].first == Max) r[i] = 0;
    }

    sort(vec.begin(), vec.end());
    int pter = vec.size() - 1;
    while (1) {
        vector <pair <int, int> > all;
        for (int i = 1; i <= peak.size(); i++) if (l[i] <= r[i]) all.push_back({(l[i] + r[i]) / 2, i});
        if (all.size() == 0) break;

        sort(all.begin(), all.end(), greater <pair <int, int> >());
        disj dsu2; dsu2.init(n * m);
        int pt = 0, pter = vec.size() - 1;

        for (int i = 0; i < all.size(); i = pt) {
            while (pt < all.size() && all[pt].first == all[i].first) pt++;
            int cur = pter - 1;
            while (pter > 0 && vec[pter - 1].first >= all[i].first) pter--;
            for (int j = pter; j <= cur; j++) {
                for (int k = 0; k < 8; k++) {
                    if (inside(vec[j].second.first + dx[k], vec[j].second.second + dy[k])) {
                        if (a[vec[j].second.first + dx[k]][vec[j].second.second + dy[k]] >= all[i].first)
                            dsu2.join(enc(vec[j].second.first, vec[j].second.second), enc(vec[j].second.first + dx[k], vec[j].second.second + dy[k]));
                    }
                }
            }

            for (int j = i; j < pt; j++) {
                int x = peak[all[j].second - 1].second.first;
                int y = peak[all[j].second - 1].second.second;
                if (dsu2.Max[dsu2.Find(enc(x, y))] > a[x][y]) l[all[j].second] = all[j].first + 1;
                else r[all[j].second] = all[j].first - 1;
            }
        }
    }

    vector <pair <int, int> > ans;
    for (int i = 1; i <= peak.size(); i++) ans.push_back({peak[i - 1].first, r[i]});
    sort(ans.begin(), ans.end(), greater <pair <int, int> >());
    printf("%d\n", (int)ans.size());
    for (auto i: ans) printf("%d %d\n", i.first, i.second);
    return 0;
}
