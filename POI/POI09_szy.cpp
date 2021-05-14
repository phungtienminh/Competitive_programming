#include <bits/stdc++.h>

using namespace std;

const int N = 45;
int a[N], n, tot;
vector <pair <int, int> > suml, sumr;

void bt (int sum, int res, int pos, int type) {
    if (type == 0 && pos == n / 2 + 1) {
        suml.push_back(make_pair(sum, res));
        return;
    }

    if (type == 1 && pos == n + 1) {
        sumr.push_back(make_pair(sum, res));
        return;
    }

    bt(sum, res, pos + 1, type);
    bt(sum + a[pos], res | (1 << (pos - (type ? n / 2 : 0) - 1)), pos + 1, type);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    cin >> tot;

    bt(0, 0, 1, 0);
    bt(0, 0, n / 2 + 1, 1);

    sort(suml.begin(), suml.end());
    sort(sumr.begin(), sumr.end());

    for (int i = 0; i < suml.size(); i++) {
        int need = tot - suml[i].first;
        int l = 0;
        int r = (int)sumr.size() - 1;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (sumr[mid].first >= need) r = mid - 1;
            else l = mid + 1;
        }

        if (l < sumr.size()) {
            if (sumr[l].first == need) {
                for (int j = 0; j < n / 2; j++) cout << ((suml[i].second >> j) & 1);
                for (int j = 0; j < n - n / 2; j++) cout << ((sumr[l].second >> j) & 1);
                return 0;
            }
        }
    }
    return 0;
}
