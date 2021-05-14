#include <bits/stdc++.h>

using namespace std;

const int N = 3e6 + 5;
const int inf = 2e9 + 2277;

int t, n, a[N];

struct Node {
    int mn, mx;
} node[2 * N];

void input(){
    scanf("%d %d", &t, &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) node[i + n].mx = node[i + n].mn = a[i];
}

void init () {
    for (int i = n - 1; i > 0; i--) {
        node[i].mn = min(node[i << 1].mn, node[i << 1 | 1].mn);
        node[i].mx = max(node[i << 1].mx, node[i << 1 | 1].mx);
    }
}

int get_min (int l, int r) {
    int res = inf;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = min(res, node[l++].mn);
        if (r & 1) res = min(res, node[--r].mn);
    }

    return res;
}

int get_max (int l, int r) {
    int res = -inf;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, node[l++].mx);
        if (r & 1) res = max(res, node[--r].mx);
    }

    return res;
}

void solve(){
    init();

    int ans = 0;
    int l = 0;
    int r = 0;

    while (l < n) {
        while (r < n - 1 && abs(get_max(l, r + 2) - get_min(l, r + 2)) <= t) r++;
        ans = max(ans, r - l + 1);
        l++;
    }

    printf("%d", ans);
}

signed main(){
    input();
    solve();
    return 0;
}
