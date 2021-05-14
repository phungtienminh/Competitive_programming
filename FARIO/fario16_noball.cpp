#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

vector <int> vrow, vcol, rows[N];
int n, q, row[N], col[N];

struct Query {
    int r1, r2, c1, c2;
} queries[N];

struct SegmentTree {
    struct Node {
        vector <int> f, g;
        int solve (int c1, int c2) {
            int pos1 = lower_bound(f.begin(), f.end(), c1) - f.begin();
            int pos2 = upper_bound(f.begin(), f.end(), c2) - f.begin() - 1;
            if (pos1 == f.size() || pos2 < 0) return 0;
            return g[pos2] - (pos1 ? g[pos1 - 1] : 0);
        }

        void apply (int r1, int r2) {
            int sz = 0;
            for (int i = r1; i <= r2; i++) {
                for (auto j: rows[i]) sz++;
            }

            f.resize(sz);
            int ptr = 0;
            for (int i = r1; i <= r2; i++) {
                for (auto j: rows[i]) f[ptr++] = j;
            }

            sort(f.begin(), f.end()); f.resize(unique(f.begin(), f.end()) - f.begin()); g.resize(f.size());
            for (int i = r1; i <= r2; i++) {
                for (auto j: rows[i]) {
                    int pos = lower_bound(f.begin(), f.end(), j) - f.begin();
                    if (pos == f.size()) continue;
                    g[pos]++;
                }
            }

            for (int i = 1; i < g.size(); i++) g[i] += g[i - 1];
        }
    } node[N << 2];

    void init (int i, int l, int r) {
        if (l == r) {
            node[i].apply(l, l);
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i].apply(l, r);
    }

    int query (int i, int l, int r, int a, int b, int c1, int c2) {
        if (l > r || a > r || b < l) return 0;
        if (a <= l && r <= b) return node[i].solve(c1, c2);

        int mid = l + r >> 1;
        return query(i << 1, l, mid, a, b, c1, c2) + query(i << 1 | 1, mid + 1, r, a, b, c1, c2);
    }
} it;

int main(){
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &row[i], &col[i]);
        //row[i]++; col[i]++;
        vrow.push_back(row[i]);
        vcol.push_back(col[i]);
    }

    for (int i = 1; i <= q; i++) {
        scanf("%d %d %d %d", &queries[i].r1, &queries[i].c1, &queries[i].r2, &queries[i].c2);
        //queries[i].r1++; queries[i].c1++; queries[i].r2++; queries[i].c2++;
        vrow.push_back(queries[i].r1); vrow.push_back(queries[i].r2);
        vcol.push_back(queries[i].c1); vcol.push_back(queries[i].c2);
    }

    //vrow.push_back(-1e9); vcol.push_back(-1e9);
    sort(vrow.begin(), vrow.end()); sort(vcol.begin(), vcol.end()); vrow.resize(unique(vrow.begin(), vrow.end()) - vrow.begin()); vcol.resize(unique(vcol.begin(), vcol.end()) - vcol.begin());
    for (int i = 1; i <= n; i++) row[i] = lower_bound(vrow.begin(), vrow.end(), row[i]) - vrow.begin(), col[i] = lower_bound(vcol.begin(), vcol.end(), col[i]) - vcol.begin();
    for (int i = 1; i <= q; i++) {
        queries[i].r1 = lower_bound(vrow.begin(), vrow.end(), queries[i].r1) - vrow.begin();
        queries[i].r2 = lower_bound(vrow.begin(), vrow.end(), queries[i].r2) - vrow.begin();
        queries[i].c1 = lower_bound(vcol.begin(), vcol.end(), queries[i].c1) - vcol.begin();
        queries[i].c2 = lower_bound(vcol.begin(), vcol.end(), queries[i].c2) - vcol.begin();
    }

    for (int i = 1; i <= n; i++) rows[row[i]].push_back(col[i]);
    it.init(1, 0, N - 1);
    for (int i = 1; i <= q; i++) {
        int r1 = queries[i].r1, r2 = queries[i].r2, c1 = queries[i].c1, c2 = queries[i].c2;
        int total = it.query(1, 0, N - 1, r1, r2, c1, c2);

        int l = r1, r = r2;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (it.query(1, 0, N - 1, r1, mid, c1, c2) * 2 >= total) r = mid - 1;
            else l = mid + 1;
        }

        printf("%d ", vrow[l]);
        l = c1, r = c2;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (it.query(1, 0, N - 1, r1, r2, c1, mid) * 2 >= total) r = mid - 1;
            else l = mid + 1;
        }

        printf("%d\n", vcol[l]);
    }
    return 0;
}
