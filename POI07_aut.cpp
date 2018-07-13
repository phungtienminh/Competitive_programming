#include <bits/stdc++.h>

using namespace std;

const int N = 10005;
const int mod = 1000;

int a[N], par[N], sz[N], n, res[N], cur[N];
vector <int> v[N];

int binPow (int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1) ans = (ans * x) % mod;

        x = (x * x) % mod;
        y >>= 1;
    }

    return ans;
}

int Find (int x) {
    return (par[x] == x ? x : par[x] = Find(par[x]));
}

void join (int x, int y) {
    if (Find(x) == Find(y)) return;

    sz[Find(x)] += sz[Find(y)];
    par[Find(y)] = Find(x);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        join(i, a[i]);
    }

    for (int i = 1; i <= n; i++) if (Find(i) == i && sz[i] % 2 == 0) return cout << 0, 0;
    int ans = 1;
    for (int i = 1; i <= n; i++) if (Find(i) == i) ans = (ans * binPow(2, sz[i]/ 2)) % mod;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j = j + i) {
            v[j].push_back(i);
        }
    }

    memset(res, 0, sizeof(res));
    for (int i = n; i >= 1; i--) {
        if (Find(i) == i) {
            for (int j = 0; j < v[sz[i]].size(); j++) {
                int d = v[sz[i]][j];
                res[d]++;
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        cur[i] = res[i] * (res[i] - 1) / 2;
        for (int j = i * 2; j <= n; j = j + i) cur[i] -= cur[j];

        ans = (ans * binPow(2, i * cur[i])) % mod;
    }

    printf("%d", ans);
    return 0;
}
