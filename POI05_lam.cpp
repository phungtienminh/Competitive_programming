#include <bits/stdc++.h>

using namespace std;

const int N = 6e4 + 5;
const int inf = 1e9 + 2277;

pair <int, int> a[N];
int n, dp[N], node[4 * N], lazy[4 * N];

void init (int i, int l, int r) {
    if (l > r) return;
    if (l == r) {
        node[i] = lazy[i] = 0;
        return;
    }

    int m = (l + r) >> 1;
    init(i << 1, l, m);
    init(i << 1 | 1, m + 1, r);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
    lazy[i] = 0;
}

void dolazy (int i, int l, int r) {
    if (lazy[i]) {
        node[i] = max(node[i], lazy[i]);
        if (l != r) {
            lazy[i << 1] = max(lazy[i << 1], lazy[i]);
            lazy[i << 1 | 1] = max(lazy[i << 1 | 1], lazy[i]);
        }

        lazy[i] = 0;
    }
}

void update (int i, int l, int r, int a, int b, int val) {
    dolazy(i, l, r);
    if (l > r || a > r || b < l) return;
    if (a <= l && r <= b) {
        node[i] = max(node[i], val);
        if (l != r) {
            lazy[i << 1] = max(lazy[i << 1], val);
            lazy[i << 1 | 1] = max(lazy[i << 1 | 1], val);
        }
        return;
    }

    int m = (l + r) >> 1;
    update(i << 1, l, m, a, b, val);
    update(i << 1 | 1, m + 1, r, a, b, val);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
}

int get (int i, int l, int r, int a, int b) {
    if (l > r || a > r || b < l) return 0;
    dolazy(i, l, r);
    if (a <= l && r <= b) return node[i];

    int m = (l + r) >> 1;
    return max(get(i << 1, l, m, a, b), get(i << 1 | 1, m + 1, r, a, b));
}

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x++; y++;
        a[i].first = y - x;
        a[i].second = x + y;
    }
}

void solve(){
    int ans = 0;
    sort(a + 1, a + n + 1);
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; ) {
        int l = i;
        int r = n;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (a[mid].first > a[i].first) r = mid - 1;
            else l = mid + 1;
        }

        for (int j = i; j <= r; j++) dp[j] = max(dp[j], get(1, 1, N, 1, a[j].second - 1) + 1);
        for (int j = i; j <= r; j++) update(1, 1, N, a[j].second, N, dp[j]);

        i = l;
    }

    for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
    printf("%d", ans);
}

int main(){
    input();
    init(1, 1, N);
    solve();
    return 0;
}
