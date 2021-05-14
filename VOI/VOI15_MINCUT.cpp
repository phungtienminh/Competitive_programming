#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int m, n, k, a[N][N];
long long f[N][N];

long long query (int x, int y, int x2, int y2) {
    return f[x2][y2] - f[x - 1][y2] - f[x2][y - 1] + f[x - 1][y - 1];
}

int main(){
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]), f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + a[i][j];
    while (k--) {
        int x, y, u, v;
        scanf("%d %d %d %d", &x, &y, &u, &v);
        long long sum = query(x, y, u, v);

        long long ans = 1e18;
        if (y != v) {
            int l = y, r = v - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                long long temp = query(x, y, u, mid);
                if (temp <= sum - temp) l = mid + 1;
                else r = mid - 1;
            }

            if (r >= y && r <= v - 1) ans = min(ans, abs(2 * query(x, y, u, r) - sum));
            if (l >= y && l <= v - 1) ans = min(ans, abs(2 * query(x, y, u, l) - sum));
        }

        if (x != u) {
            int l = x, r = u - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                long long temp = query(x, y, mid, v);
                if (temp <= sum - temp) l = mid + 1;
                else r = mid - 1;
            }

            if (r >= x && r <= u - 1) ans = min(ans, abs(2 * query(x, y, r, v) - sum));
            if (l >= x && l <= u - 1) ans = min(ans, abs(2 * query(x, y, l, v) - sum));
        }

        printf("%lld\n", ans);
    }
    return 0;
}
