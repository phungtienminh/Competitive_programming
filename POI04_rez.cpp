#include <bits/stdc++.h>

using namespace std;

const int N = 10005;

struct Data {
    int l, r;

    bool operator<(const Data &other) const                         {
        return r < other.r;
    }
} a[N];

int dp[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r;

    sort(a + 1, a + n + 1);
    memset(dp, 0, sizeof(dp));

    dp[0] = 0;
    dp[1] = a[1].r - a[1].l;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1];
        int l = 1;
        int r = i - 1;

        while (l <= r) {
            int mid = (l + r) >> 1;
            if (a[mid].r <= a[i].l) l = mid + 1;
            else r = mid - 1;
        }

        dp[i] = max(dp[i], dp[r] + a[i].r - a[i].l);
    }

    cout << dp[n];
    return 0;
}
