#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], b[N], ans = 0;
map <int, int> mm;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) mm[b[i] - a[i]]++;
    for (auto it: mm) ans = max(ans, it.second);
    cout << ans;
    return 0;
}
