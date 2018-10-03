#include <bits/stdc++.h>

using namespace std;

const int N = 505;

pair <int, int> a[N], b[N], p;
int n;
bool used[N];

bool inside (pair <int, int> x, pair <int, int> y, pair <int, int> z) {
    return y.first >= min(x.first, z.first) && y.first <= max(x.first, z.first) && y.second >= min(x.second, z.second) && y.second <= max(x.second, z.second);
}

bool intersect (int idx, pair <int, int> x, pair <int, int> y) {
    return max(x.first, a[idx].first) <= min(y.first, b[idx].first) && max(x.second, a[idx].second) <= min(y.second, b[idx].second);
}

bool check (int mid) {
    int lx = -mid + 1, ly = -mid + 1, rx = mid - 1, ry = mid - 1;
    memset(used, 0, sizeof(used));
    while (!inside({lx, ly}, p, {rx, ry})) {
        bool hasIntersect = false;
        for (int i = 1; i <= n; i++) {
            if (!used[i] && intersect(i, {lx, ly}, {rx, ry})) {
                used[i] = true;
                lx = min(lx, a[i].first);
                ly = min(ly, a[i].second);
                rx = max(rx, b[i].first);
                ry = max(ry, b[i].second);
                hasIntersect = true;
            }
        }

        if (!hasIntersect) return true;
    }

    return false;
}

int main(){
    scanf("%d %d", &p.first, &p.second);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d %d %d", &a[i].first, &a[i].second, &b[i].first, &b[i].second);
    for (int i = 1; i <= n; i++) if (a[i] > b[i]) swap(a[i], b[i]);

    int l = 1, r = 1e6 + 5;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }

    printf("%d", r);
    return 0;
}
