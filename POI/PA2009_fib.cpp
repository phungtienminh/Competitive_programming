#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int lazy[4 * N], n, q, fib[N];

struct Node {
    int sum, nxt;
} node[4 * N];

void init (int i, int l, int r) {
    if (l > r) return;
    if (l == r) {
        node[i].sum = fib[0];
        node[i].nxt = fib[1];
        lazy[i] = 0;
        return;
    }

    int m = (l + r) >> 1;
    init(i << 1, l, m);
    init(i << 1 | 1, m + 1, r);

    node[i].sum = (node[i << 1].sum + node[i << 1 | 1].sum) % mod;
    node[i].nxt = (node[i << 1].nxt + node[i << 1 | 1].nxt) % mod;
    lazy[i] = 0;
}

void dolazy (int i, int l, int r) {
    //it[x] = it[x] * fib[y - 1] + it[x + 1] * fib[y];
    if (lazy[i]) {
        int temp = node[i].sum;
        node[i].sum = (1LL * node[i].sum * fib[lazy[i] - 1] + 1LL * node[i].nxt * fib[lazy[i]]) % mod;
        node[i].nxt = (1LL * temp * fib[lazy[i]] + 1LL * node[i].nxt * fib[lazy[i] + 1]) % mod;

        if (l != r) {
            lazy[i << 1] += lazy[i];
            lazy[i << 1 | 1] += lazy[i];
        }

        lazy[i] = 0;
    }
}

void update (int i, int l, int r, int a, int b) {
    dolazy(i, l, r);
    if (l > r || a > r || b < l) return;
    if (a <= l && r <= b) {
        int temp = node[i].sum;
        node[i].sum = node[i].nxt;
        node[i].nxt = (temp + node[i].nxt) % mod;

        if (l != r) {
            lazy[i << 1]++;
            lazy[i << 1 | 1]++;
        }

        return;
    }

    int m = (l + r) >> 1;
    update(i << 1, l, m, a, b);
    update(i << 1 | 1, m + 1, r, a, b);

    node[i].sum = (node[i << 1].sum + node[i << 1 | 1].sum) % mod;
    node[i].nxt = (node[i << 1].nxt + node[i << 1 | 1].nxt) % mod;
}

int get (int i, int l, int r, int a, int b) {
    if (l > r || a > r || b < l) return 0;
    dolazy(i, l, r);
    if (a <= l && r <= b) return node[i].sum;

    int m = (l + r) >> 1;
    return (get(i << 1, l, m, a, b) + get(i << 1 | 1, m + 1, r, a, b)) % mod;
}

void input(){
    scanf("%d %d", &n, &q);
}

void prep(){
    fib[0] = 0; fib[1] = 1;
    for (int i = 2; i < N; i++) fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
}

void solve(){
    prep();
    init(1, 1, n);
    while (q--) {
        char s[2];
        int l, r;
        scanf("%s %d %d", s, &l, &r);

        if (s[0] == 'D') update(1, 1, n, l, r);
        else printf("%d\n", get(1, 1, n, l, r));
    }
}

int main(){
    input();
    solve();
    return 0;
}
