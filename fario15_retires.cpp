#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, b, f, ptrcol[N];
vector <int> rowb[N], rowf[N], colb[N], colf[N];

struct SegmentTree {
    int node[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = 0;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = max(node[i << 1], node[i << 1 | 1]);
    }

    void update (int i, int l, int r, int pos, int val, int type) {
        if (l == r) {
            if (!type) node[i] = val;
            else node[i] += val;
            return;
        }

        int mid = l + r >> 1;
        if (pos <= mid) update(i << 1, l, mid, pos, val, type);
        else update(i << 1 | 1, mid + 1, r, pos, val, type);
        node[i] = max(node[i << 1], node[i << 1 | 1]);
    }

    int query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        if (a <= l && r <= b) return node[i];

        int mid = l + r >> 1;
        return max(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
    }
} it;

int main(){
    scanf("%d %d %d %d", &n, &m, &b, &f);
    for (int i = 1; i <= b; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        rowb[x].push_back(y);
        colb[y].push_back(x);
    }

    for (int i = 1; i <= f; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        rowf[x].push_back(y);
        colf[y].push_back(x);
    }

    for (int i = 1; i <= n; i++) sort(rowb[i].begin(), rowb[i].end()), sort(rowf[i].begin(), rowf[i].end());
    for (int i = 1; i <= m; i++) sort(colb[i].begin(), colb[i].end()), sort(colf[i].begin(), colf[i].end());

    int ans = 0;
    it.init(1, 1, n);
    for (int i = 1; i <= m; i++) {
        if (i == 1) {
            for (int j = 1; j <= n; j++) {
                int pos = lower_bound(rowb[j].begin(), rowb[j].end(), 0) - rowb[j].begin();
                if (pos == rowb[j].size()) pos = m;
                else pos = rowb[j][0];
                if (rowf[j].size() == 0) continue;
                int p = upper_bound(rowf[j].begin(), rowf[j].end(), pos) - rowf[j].begin();
                it.update(1, 1, n, j, p, 0);
            }
        }

        for (int j = 0; j < colb[i - 1].size(); j++) {
            int temp = colb[i - 1][j];
            int nblock = upper_bound(rowb[temp].begin(), rowb[temp].end(), i - 1) - rowb[temp].begin();
            int nfruit = upper_bound(rowf[temp].begin(), rowf[temp].end(), i - 1) - rowf[temp].begin();
            if (nblock == rowb[temp].size()) it.update(1, 1, n, temp, rowf[temp].size() - nfruit, 0);
            else {
                int pos = upper_bound(rowf[temp].begin(), rowf[temp].end(), rowb[temp][nblock]) - rowf[temp].begin();
                it.update(1, 1, n, temp, pos - nfruit, 0);
            }
        }

        for (int j = 0; j < colb[i].size(); j++) it.update(1, 1, n, colb[i][j], 0, 0);
        for (int j = 0; j < colf[i].size(); j++) it.update(1, 1, n, colf[i][j], -1, 1);
        if (colb[i].size() == 0) ans = max(ans, (int)colf[i].size() + it.query(1, 1, n, 1, n));
        else {
            for (int j = 0; j < colb[i].size(); j++) {
                if (j == 0) {
                    int pos = lower_bound(colf[i].begin(), colf[i].end(), colb[i][j]) - colf[i].begin();
                    ans = max(ans, pos + it.query(1, 1, n, 1, colb[i][j] - 1));
                }
                if (j == colb[i].size() - 1) {
                    int pos = lower_bound(colf[i].begin(), colf[i].end(), colb[i][j]) - colf[i].begin();
                    ans = max(ans, (int)colf[i].size() - pos + it.query(1, 1, n, colb[i][j] + 1, n));
                }
                if (j + 1 < colb[i].size()) {
                    int pos = lower_bound(colf[i].begin(), colf[i].end(), colb[i][j]) - colf[i].begin();
                    int pos2 = lower_bound(colf[i].begin(), colf[i].end(), colb[i][j + 1]) - colf[i].begin();
                    ans = max(ans, pos2 - pos + it.query(1, 1, n, colb[i][j] + 1, colb[i][j + 1] - 1));
                }
            }
        }
        for (int j = 0; j < colf[i].size(); j++) it.update(1, 1, n, colf[i][j], 1, 1);
    }

    printf("%d", ans);
    return 0;
}
