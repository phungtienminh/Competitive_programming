#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], dp[N];

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
}

void solve(){
    if (n == 1) {
        printf("%d", a[1]);
        return;
    }

    dp[1] = a[1]; dp[2] = a[2];
    for (int i = 3; i <= n; i++) dp[i] = min(dp[i - 1] + a[1] + a[i], dp[i - 2] + a[1] + a[i] + a[2] + a[2]);
    printf("%d", dp[n]);
}

int main(){
    input();
    solve();
    return 0;
}
