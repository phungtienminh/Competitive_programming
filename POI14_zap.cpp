#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;
const int block = 100;

struct Query {
    int a, b, id;

    bool operator<(const Query &other) const {
        if (a / block != other.a / block) return a / block < other.a / block;
        return b < other.b;
    }
};

int n, a, b, d, factor_cnt[N], ans[N], prime_factor[N][8];
int L = 0;
int R = 0;
Query queries[N];

int calc (int a, int b) {
    int res = 0;
    int sz = factor_cnt[a];
    int mask = 1 << sz;

    for (int i = 0; i < mask; i++) {
        int cur = 1;
        for (int j = 0; j < sz; j++) if (i & (1 << j)) cur *= -prime_factor[a][j];

        res += b / cur;
    }

    return res;
}

int readInt(){
    int res = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') break;

        res = res * 10 + (c - '0');
    }

    return res;
}

signed main(){
    n = readInt();

    memset(factor_cnt, 0, sizeof(factor_cnt));
    for (int i = 2; i < N; i++) {
        if (!factor_cnt[i]) {
            for (int j = i; j < N; j = j + i) prime_factor[j][factor_cnt[j]++] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        a = readInt(); b = readInt(); d = readInt();
        a /= d; b /= d;
        queries[i].a = a; queries[i].b = b; queries[i].id = i;
    }

    sort(queries, queries + n);
    int res = 0;
    for (int i = 0; i < n; i++) {
        while (L < queries[i].a) res += calc(++L, R);
        while (R < queries[i].b) res += calc(++R, L);

        while (L > queries[i].a) res -= calc(L--, R);
        while (R > queries[i].b) res -= calc(R--, L);

        ans[queries[i].id] = res;
    }

    for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
    return 0;
}
