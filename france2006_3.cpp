#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, k, dp[N];

int calc (int cur, int lim) {
    if (cur > lim) return 0;
    if (cur == lim) return 1;
    int &ans = dp[cur];
    if (ans != -1) return ans;

    ans = 1;
    for (int i = 1; i <= k; i++) {
        ans += calc(cur + i, lim);
        ans = min(ans, (int)1e9);
    }

    return ans;
}

bool check (int mid) {
    memset(dp, -1, sizeof(dp));
    return calc(0, mid) >= n;
}

int main(){
    scanf("%d %d", &n, &k);
    int l = 0, r = N - 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid - 1;
        else l = mid + 1;
    }

    printf("%d", l);
    return 0;
}
