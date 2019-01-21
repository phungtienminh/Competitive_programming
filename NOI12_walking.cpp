#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int l, n, dp[N];
pair <int, int> a[N];

int main(){
    scanf("%d %d", &l, &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1);

    for (int i = n; i >= 1; i--) {
        dp[i] = 1;
        for (int j = i + 1; j <= n; j++) {
            if (l * a[j].second + a[i].first * a[i].second * a[j].second > l * a[i].second + a[j].first * a[i].second * a[j].second) dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    printf("%d", *max_element(dp + 1, dp + n + 1));
    return 0;
}
