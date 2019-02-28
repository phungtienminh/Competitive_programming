#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, a[N], ans = 1e9, res = 0;
vector <int> even, odd;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) even.push_back(m - a[i] + 1);
        else odd.push_back(a[i]);
    }

    sort(even.begin(), even.end()); sort(odd.begin(), odd.end());
    for (int i = 1; i <= m; i++) {
        int sum = lower_bound(odd.begin(), odd.end(), i) - odd.begin();
        sum = odd.size() - sum;
        sum += upper_bound(even.begin(), even.end(), i) - even.begin();
        if (sum < ans) {
            ans = sum;
            res = 1;
        }
        else if (sum == ans) res++;
    }

    cout << ans << " " << res;
    return 0;
}
