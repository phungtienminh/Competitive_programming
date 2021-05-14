#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, x, y, f[N], g[N], ans = 2e9;
pair <int, int> a[N];

int main(){
    scanf("%d %d %d", &n, &x, &y);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] + (a[i].second == 1), g[i] = g[i - 1] + (a[i].second == 2);

    int l = 1, r = 1;
    while (l <= n) {
        while (r <= n && (f[r] - f[l - 1] < x || g[r] - g[l - 1] < y)) r++;
        if (f[r] - f[l - 1] >= x && g[r] - g[l - 1] >= y) ans = min(ans, a[r].first - a[l].first);
        l++;
    }

    printf("%d", ans > 15e8 ? -1 : ans);
    return 0;
}
