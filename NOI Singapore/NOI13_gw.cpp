#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, res = 0, ans = 0;
pair <int, int> a[N];

struct disj {
    int par[N];
    bool mark[N];
    void init (int n) {
        iota(par + 1, par + n + 1, 1);
        memset(mark, 0, sizeof(mark));
    }

    int Find (int x) {
        return par[x] == x ? x : par[x] = Find(par[x]);
    }

    void join (int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;
        par[y] = x;
        mark[x] |= mark[y];
    }
} dsu;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i].first), a[i].second = i;
    sort(a + 1, a + n + 1, greater <pair <int, int> >());

    int ptr = 1;
    dsu.init(n);
    for (int i = 1; i <= n; i = ptr) {
        while (ptr <= n && a[ptr].first == a[i].first) {
            if (a[ptr].second == n) {
                if (dsu.mark[dsu.Find(a[ptr].second - 1)]) dsu.join(a[ptr].second, a[ptr].second - 1);
                else res++, dsu.mark[a[ptr].second] = true;
            }
            else if (a[ptr].second == 1) {
                if (dsu.mark[dsu.Find(a[ptr].second + 1)]) dsu.join(a[ptr].second, a[ptr].second + 1);
                else res++, dsu.mark[a[ptr].second] = true;
            }
            else {
                if (dsu.mark[dsu.Find(a[ptr].second - 1)]) {
                    if (dsu.mark[dsu.Find(a[ptr].second + 1)]) {
                        dsu.join(a[ptr].second, a[ptr].second - 1);
                        dsu.join(a[ptr].second, a[ptr].second + 1);
                        res--;
                    }
                    else dsu.join(a[ptr].second, a[ptr].second - 1);
                }
                else {
                    if (dsu.mark[dsu.Find(a[ptr].second + 1)]) dsu.join(a[ptr].second, a[ptr].second + 1);
                    else res++, dsu.mark[a[ptr].second] = true;
                }
            }

            ptr++;
        }

        ans = max(ans, res);
    }

    printf("%d", ans);
    return 0;
}
