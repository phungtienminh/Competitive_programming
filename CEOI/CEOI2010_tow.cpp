#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
const int mod = 1e9 + 9;

int n, d, a[N];

int main(){
    scanf("%d %d", &n, &d);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        int nxt = upper_bound(a + 1, a + n + 1, a[i] + d) - a;
        ans = (1LL * ans * (nxt - i)) % mod;
    }

    printf("%d", ans);
    return 0;
}
