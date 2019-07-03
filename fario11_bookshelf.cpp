#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, k, a[N], d[N], ans = 0;
bool b[N];
queue <int> q;

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memset(d, 0x3f, sizeof(d));

    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        d[x] = 0; q.push(x);
    }

    for (int i = 1; i <= k; i++) {
        int x;
        scanf("%d", &x);
        b[x] = true;
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u > 1 && d[u - 1] > d[u] + 1 && a[u - 1] >= a[u]) {
            d[u - 1] = d[u] + 1;
            q.push(u - 1);
        }

        if (u < n && d[u + 1] > d[u] + 1 && a[u + 1] >= a[u]) {
            d[u + 1] = d[u] + 1;
            q.push(u + 1);
        }
    }

    for (int i = 1; i <= n; i++) ans += (d[i] <= 1e9 && b[i]);
    printf("%d", ans);
    return 0;
}
