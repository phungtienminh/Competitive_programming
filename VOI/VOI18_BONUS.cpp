#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, k, r, p, a[N][N], x[15], y[15];
long long f[N][N];

void update (int &x, int &y, int x2, int y2) {
    if (x2 < x) x = x2;
    if (y2 < y) y = y2;
}

void update2 (int &x, int &y, int x2, int y2) {
    if (x2 > x) x = x2;
    if (y2 > y) y = y2;
}

long long query (int x, int y, int x2, int y2) {
    return f[x2][y2] - f[x2][y - 1] - f[x - 1][y2] + f[x - 1][y - 1];
}

bool overlap (int x, int y, int x2, int y2, int x3, int y3, int x4, int y4) {
    if (y4 < y || y2 < y3) return false;
    if (x4 < x || x2 < x3) return false;
    return true;
}

int main(){
    #ifndef Futymy
        freopen("bonus.inp", "r", stdin);
        freopen("bonus.out", "w", stdout);
    #endif // Futymy

    scanf("%d %d %d %d", &n, &k, &r, &p);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]), f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + a[i][j];
    long long ans = 0;

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < p; j++) scanf("%d %d", &x[j], &y[j]);
        long long res = 0;

        for (int mask = 1; mask < (1 << p); mask++) {
            long long cur = 0;
            int ux = 0, uy = 0, dx = 1e9, dy = 1e9;
            /*vector <pair <pair <int, int>, pair <int, int> > > vec;
            bool f = true;
            for (int j = 0; j < p; j++) if (mask & (1 << j)) vec.push_back({{x[j], y[j]}, {x[j] + r - 1, y[j] + r - 1}});
            for (int j = 0; j < vec.size(); j++) {
                for (int nxt = j + 1; nxt < vec.size(); nxt++) {
                    if (!overlap(vec[j].first.first, vec[j].first.second, vec[j].second.first, vec[j].second.second,
                                 vec[nxt].first.first, vec[nxt].first.second, vec[nxt].second.first, vec[nxt].second.second)) {
                                    f = false;
                                    break;
                                 }
                    if (!f) break;
                }
            }

            if (!f) continue;*/
            for (int j = 0; j < p; j++) {
                if (mask & (1 << j)) {
                    update(dx, dy, x[j] + r - 1, y[j] + r - 1);
                    update2(ux, uy, x[j], y[j]);
                }
            }

            int sx = max(0, dx - ux + 1);
            int sy = max(0, dy - uy + 1);
            if (sx > 0 && sy > 0) cur = query(ux, uy, dx, dy);

            if (__builtin_popcount(mask) % 2 == 1) res += cur;
            else res -= cur;

            //cout << cur << "\n";
            //cout << "COOR " << ux << " " << uy << " " << dx << " " << dy << "\n";
        }

        //cout << res << "\n";
        ans = max(ans, res);
    }

    printf("%lld", ans);
    return 0;
}
/*
4 2 2 3
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 2 2 3 3
1 1 1 3 3 1
*/
