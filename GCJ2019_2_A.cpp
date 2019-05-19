#include <bits/stdc++.h>

using namespace std;

const int N = 305;

int t, n;
pair <int, int> a[N];
set <pair <int, int> > st;

void solve(){
    cin >> n; st.clear();
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i].first <= a[j].first && a[i].second <= a[j].second) continue;
            if (a[i].first >= a[j].first && a[i].second >= a[j].second) continue;
            int d1 = a[i].first - a[j].first;
            int d2 = a[j].second - a[i].second;
            int g = __gcd(d1, d2);
            d1 /= g; d2 /= g;
            st.insert({d1, d2});
        }
    }

    cout << st.size() + 1;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int T = 1; T <= t; T++) {
        cout << "Case #" << T << ": ";
        solve();
        cout << "\n";
    }
    return 0;
}
