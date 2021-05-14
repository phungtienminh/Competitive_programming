#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int maxn = 35;

int n, m, l, a[105][maxn], b[N];

int main(){
    scanf("%d %d %d", &n, &m, &l);
    int lim = 0;
    for (int i = 0; i < 31; i++) lim |= (1 << i);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= l; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) {
        int ans = 0, num = 0, cur = 0;
        for (int j = m; j <= 30; j++) num |= (1 << j);
        for (int j = 1; j <= m; j++) if (a[i][j]) num |= (1 << (j - 1));
        for (int j = 1; j <= m; j++) if (b[j]) cur |= (1 << (j - 1));
        //if (i == 2) cout << "DEBUG\n" << num << " " << cur << "\nDEBUG\n";
        for (int j = 1; j + m - 1 < l; j++) {
            ans = max(ans, __builtin_popcount(num ^ cur ^ lim));
            cur >>= 1;
            if (b[j + m]) cur |= (1 << (m - 1));
        }

        ans = max(ans, __builtin_popcount(num ^ cur ^ lim));
        printf("%d\n", m - ans);
    }
    return 0;
}
