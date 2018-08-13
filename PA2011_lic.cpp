#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
const int maxn = 3e6 + 5;

int n, a[N];
int Max = 0;
long long cnt[maxn], dp[maxn];

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
}

void solve(){
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) Max = max(Max, a[i]);
    for (int i = 1; i <= n; i++) cnt[a[i]]++;
    for (int i = 1; i < Max + 1; i++) {
        for (int j = i * 2; j < Max + 1; j = j + i) {
            cnt[i] += cnt[j];
        }
    }

    for (int i = Max; i >= 1; i--) {
        dp[i] = cnt[i] * (cnt[i] - 1) / 2;
        for (int j = i * 2; j < Max + 1; j = j + i) dp[i] = dp[i] - dp[j];
    }

    printf("%lld", dp[1]);
}

int main(){
    input();
    solve();
    return 0;
}
