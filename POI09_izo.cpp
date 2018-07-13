#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;
int a[N];

signed main() {
    int n;
    scanf("%lld", &n);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        ans += a[i];
    }

    sort(a + 1, a + n + 1);
    /*int mx = 0;
    do {
        int res = ans;
        for (int i = 1; i <= n - 1; i++) res = res + max(0LL, a[i + 1] - a[i]);
        for (int i = 1; i <= n; i++) cout << a[i] << " ";
        cout << res << "\n";

        mx = max(mx, res);
    } while (next_permutation(a + 1, a + n + 1));

    cout << mx;*/

    int l = 1;
    int r = n;
    vector <int> v;
    while (l <= r) {
        v.push_back(a[l]);
        if (l != r) v.push_back(a[r]);
        l++; r--;
    }

    for (int i = 1; i < v.size(); i++) ans = ans + max(0LL, v[i] - v[i - 1]);
    printf("%lld", ans);
    return 0;
}
