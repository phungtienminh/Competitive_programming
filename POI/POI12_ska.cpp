#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int par[N], n;

void init (int n) {
    for (int i = 1; i <= n; i++) par[i] = i;
}

int Find (int x) {
    return (par[x] == x ? x : par[x] = Find(par[x]));
}

bool same (int x, int y) {
    return (Find(x) == Find(y));
}

void Union (int x, int y) {
    if (same(x, y)) return;

    par[Find(y)] = Find(x);
}

int main(){
    scanf("%d", &n);
    int ans = n;
    init(n);

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        if (!same(x, i)) {
            ans--;
            Union(x, i);
        }
    }

    printf("%d", ans);
    return 0;
}
