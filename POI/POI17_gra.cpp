#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 5;
int n, a[N];

void input(){
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
}

void solve(){
    int ans = 0;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) ans = max(ans, a[i] - ans);
    printf("%lld", ans);
}

signed main(){
    input();
    solve();
    return 0;
}
