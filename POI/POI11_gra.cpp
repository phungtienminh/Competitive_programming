#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int a[N], b[N], m, n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> n;
    for (int i = 0; i < n; i++) cin >> b[i];
    b[n] = m + 1;

    int diff = 0;
    for (int i = n - 1; i >= 0; i--) {
        diff += (b[i + 1] - b[i] - 1);
        a[n - i - 1] = diff;
    }

    vector <pair <int, int> > v;
    int tot = 0;
    int l = 0;

    while (l < n) {
        int r = l;
        while (r < n && a[l] == a[r]) r++;
        v.push_back(make_pair(a[l], r - l));
        if (a[l] & 1) tot ^= r - l;
        l = r;
    }

    if (v[0].first == 1) return cout << v[0].second, 0;

    int ans = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first == 2) continue;
        if (v[i].first & 1) {
            for (int j = 1; j <= v[i].second; j++) {
                int cur = tot ^ v[i].second ^ (v[i].second - j);
                if (cur == 0) ans++;
            }
        }
        else {
            if (i > 0 && v[i - 1].first + 1 == v[i].first) {
            for (int j = 1; j <= v[i].second; j++) {
                int cur = tot ^ v[i - 1].second ^ (v[i - 1].second + j);
                if (cur == 0) ans++;
            }
            }
            else {
                for (int j = 1; j <= v[i].second; j++) {
                    int cur = tot ^ j;
                    if (cur == 0) ans++;
                }
            }
        }
    }

    cout << ans;
    return 0;
}
