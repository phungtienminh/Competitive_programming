#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n;
pair <long long, long long> a[N];
long long ans = -1e18, res = -1e18;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld %lld", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) a[i].second += a[i - 1].second;
    for (int i = 1; i <= n; i++) {
        res = max(res, a[i].first - a[i - 1].second);
        ans = max(ans, a[i].second - a[i].first + res);
    }

    printf("%lld", ans);
    return 0;
}
