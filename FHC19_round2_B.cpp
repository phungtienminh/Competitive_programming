#include <bits/stdc++.h>

using namespace std;

const int N = 4005;

int t, n, m, dp[N][N + N], cnt = 0, res[N];
vector <int> vec[N];
pair <int, int> trace[N][N + N];

struct disj {
    int par[N], sz[N], ndsu;
    void init (int n) {
        iota(par + 1, par + n + 1, 1);
        fill(sz + 1, sz + n + 1, 1);
        ndsu = n;
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
        sz[x] += sz[y];
        ndsu--;
    }
};

void solve (int Test) {
    scanf("%d %d", &n, &m); memset(dp, 0, sizeof(dp)); memset(trace, -1, sizeof(trace));
    for (int i = 1; i <= n; i++) vec[i].clear();
    disj dsu;
    dsu.init(n); cnt = 0;

    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        int ptl = l, ptr = r;
        while (ptl < ptr) {
            dsu.join(ptl, ptr);
            ptl++;
            ptr--;
        }
    }

    map <int, int> mm;
    for (int i = 1; i <= n; i++) {
        int x = dsu.Find(i);
        if (!mm.count(x)) mm[x] = ++cnt;
    }

    for (int i = 1; i <= n; i++) vec[mm[dsu.Find(i)]].push_back(i);
    assert(cnt == dsu.ndsu);
    dp[0][N] = 1;
    for (int i = 0; i < dsu.ndsu; i++) {
        for (int j = 0; j < N + N; j++) {
            if (dp[i][j]) {
                dp[i + 1][j + vec[i + 1].size()] = dp[i][j];
                trace[i + 1][j + vec[i + 1].size()] = {0, j};
                dp[i + 1][j - vec[i + 1].size()] = dp[i][j];
                trace[i + 1][j - vec[i + 1].size()] = {1, j};
            }
        }
    }

    int ans = 1e9, pos = 0;
    for (int i = 0; i < N + N; i++) {
        if (dp[dsu.ndsu][i]) {
            if (abs(N - i) < ans)
                ans = abs(N - i), pos = i;
        }
    }

    int cur = dsu.ndsu;
    while (cur > 0) {
        for (int i = 0; i < vec[cur].size(); i++) res[vec[cur][i]] = trace[cur][pos].first;
        pos = trace[cur][pos].second;
        cur--;
    }

    printf("Case #%d: ", Test);
    for (int i = 1; i <= n; i++) printf("%d", res[i]);
    puts("");
}

int main(){
    freopen("bitstrings_as_a_service.txt", "r", stdin);
    freopen("contestant.out", "w", stdout);
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) solve(i);
    return 0;
}
