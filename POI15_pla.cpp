#include <bits/stdc++.h>

using namespace std;

const int N = 25e4 + 5;

int n, d[N], w[N], node[4 * N];

void init (int i, int l, int r) {
    if (l > r) return;
    if (l == r) {
        node[i] = l;
        return;
    }

    int m = (l + r) >> 1;
    init(i << 1, l, m);
    init(i << 1 | 1, m + 1, r);
    node[i] = (w[node[i << 1]] < w[node[i << 1 | 1]] ? node[i << 1] : node[i << 1 | 1]);
}

int get (int i, int l, int r, int a, int b) {
    if (l > r || a > r || b < l) return 0;
    if (a <= l && r <= b) return node[i];

    int m = (l + r) >> 1;
    int left = get(i << 1, l, m, a, b);
    int right = get(i << 1 | 1, m + 1, r, a, b);

    if (!left) return right;
    if (!right) return left;
    return (w[left] < w[right] ? left : right);
}

int query (int l, int r, int h) {
    if (l > r) return 0;

    int idx_min = get(1, 1, n, l, r);
    int ans = query(l, idx_min - 1, w[idx_min]) + query(idx_min + 1, r, w[idx_min]);

    if (w[idx_min] > h) ans++;
    return ans;
}

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &d[i], &w[i]);
}

void solve(){
    init(1, 1, n);
    printf("%d", query(1, n, 0));
}

int main(){
    input();
    solve();
    return 0;
}
