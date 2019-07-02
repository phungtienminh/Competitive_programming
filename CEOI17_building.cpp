#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const long long inf = 1LL << 62;
const int maxn = 1e6 + 5;

int n, h[N], w[N];
long long dp[N], f[N];

struct Line {
    int a;
    long long b;
    Line (int a = 0, long long b = inf): a(a), b(b) {}
    long long f (int x) {
        return 1LL * a * x + b;
    }
} node[maxn << 2];

struct LiChaoTree {
    void add (int i, int l, int r, Line val) {
        if (node[i].f(l) >= val.f(l) && node[i].f(r) >= val.f(r)) {
            node[i] = val;
            return;
        }

        if (node[i].f(l) <= val.f(l) && node[i].f(r) <= val.f(r)) return;

        int mid = l + r >> 1;
        add(i << 1, l, mid, val);
        add(i << 1 | 1, mid + 1, r, val);
    }

    long long query (int i, int l, int r, int x) {
        if (l == r) return node[i].f(x);

        int mid = l + r >> 1;
        if (x <= mid) return min(node[i].f(x), query(i << 1, l, mid, x));
        return min(node[i].f(x), query(i << 1 | 1, mid + 1, r, x));
    }
} lct;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] + w[i];

    //dp(i) = max(dp(j) + f(i - 1) - f(j) + hi^2 + hj^2 - 2hihj | j < i)
    //dp(i) = max(-2hjhi + hj^2 + dp(j) - f(j) + f(i - 1) + hi^2 | j < i)
    memset(dp, 0x3f, sizeof(dp));
    dp[1] = 0;
    lct.add(1, 0, maxn - 1, Line(-2 * h[1], 1LL * h[1] * h[1] + dp[1] - f[1]));
    for (int i = 2; i <= n; i++) {
        dp[i] = lct.query(1, 0, maxn - 1, h[i]) + f[i - 1] + 1LL * h[i] * h[i];
        lct.add(1, 0, maxn - 1, Line(-2 * h[i], 1LL * h[i] * h[i] + dp[i] - f[i]));
    }

    printf("%lld", dp[n]);
    return 0;
}
/*
6
3 8 7 1 6 6
0 -1 9 1 2 0
*/
