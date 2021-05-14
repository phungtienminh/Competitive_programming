#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int par[4 * N], n, s[N], e[N], val[N];
vector <int> v;

void init (int sz) {
    for (int i = 0; i < sz; i++) par[i] = i;
}

int Find (int x) {
    return (par[x] == x ? x : par[x] = Find(par[x]));
}

void join (int x, int y) {
    x = Find(x); y = Find(y);
    if (x == y) return;

    par[y] = x;
}

void input(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &s[i], &e[i], &val[i]);
        v.push_back(--s[i]);
        v.push_back(e[i]);
    }
}

void solve(){
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    int sz = v.size();
    init(2 * sz);

    for (int i = 0; i < n; i++) {
        s[i] = (int)(lower_bound(v.begin(), v.end(), s[i]) - v.begin());
        e[i] = (int)(lower_bound(v.begin(), v.end(), e[i]) - v.begin());

        if (!val[i]) {
            join(s[i], e[i]);
            join(s[i] + sz, e[i] + sz);
        }
        else {
            join(s[i], e[i] + sz);
            join(s[i] + sz, e[i]);
        }

        if (Find(s[i]) == Find(s[i] + sz) || Find(e[i]) == Find(e[i] + sz)) {
            printf("%d", i);
            return;
        }
    }

    printf("%d", n);
}

int main(){
    input();
    solve();
    return 0;
}
