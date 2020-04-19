#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, t, a[N], b[N], dp[N], cnt = 0;
map <long long, int> mm;
vector <long long> vec;

struct SegmentTree {
    int node[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = 0;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = 0;
    }

    void update (int i, int l, int r, int pos, int val) {
        if (l == r) {
            node[i] = max(node[i], val);
            return;
        }

        int mid = l + r >> 1;
        if (pos <= mid) update(i << 1, l, mid, pos, val);
        else update(i << 1 | 1, mid + 1, r, pos, val);
        node[i] = max(node[i << 1], node[i << 1 | 1]);
    }

    int query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        if (a <= l && r <= b) return node[i];
        int mid = l + r >> 1;
        return max(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
    }
} it;

int main(){
    #ifndef Futymy
        freopen("cowjog.in", "r", stdin);
        freopen("cowjog.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        vec.push_back(a[i]);
        vec.push_back(1LL * b[i] * t + a[i]);
    }

    sort(vec.begin(), vec.end()); mm[vec[0]] = ++cnt;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[i - 1]) {
            mm[vec[i]] = ++cnt;
        }
    }

    it.init(1, 1, cnt);
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        dp[i] = max(dp[i], 1 + it.query(1, 1, cnt, mm[1LL * b[i] * t + a[i]], cnt));
        it.update(1, 1, cnt, mm[1LL * b[i] * t + a[i]], dp[i]);
    }

    cout << *max_element(dp + 1, dp + n + 1);
    return 0;
}
