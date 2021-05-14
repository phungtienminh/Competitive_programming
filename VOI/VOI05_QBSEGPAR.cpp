#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 5;

int n, k, a[N], dp[N], g[N], pos[N], cnt = 0;
vector <long long> vec;
long long f[N];
map <long long, int> mm;

struct fenwick {
    int bit[N];
    void init() {
        memset(bit, 0x3f, sizeof(bit));
    }

    void update (int pos, int val) {
        for (int i = pos; i > 0; i -= i & -i) bit[i] = min(bit[i], val);
    }

    int get (int pos) {
        int ans = 1e9;
        for (int i = pos; i < N; i += i & -i) ans = min(ans, bit[i]);
        return ans;
    }
} fenw;

struct BIT {
    int bit[N];
    void init(){
        memset(bit, -0x3f, sizeof(bit));
    }

    void update (int pos, int val) {
        for (int i = pos; i > 0; i -= i & -i) bit[i] = max(bit[i], val);
    }

    int get (int pos) {
        int ans = -5e8;
        for (int i = pos; i < N; i += i & -i) ans = max(ans, bit[i]);
        return ans;
    }
} fenw2;

bool check (long long mid) {
    memset(dp, 0x3f, sizeof(dp)); dp[0] = 0; fenw.init(); fenw2.init(); cnt = 0; vec.clear(); memset(g, 0, sizeof(g));
    vec.push_back(0); vec.push_back(-mid);
    for (int i = 1; i <= n; i++) {
        vec.push_back(f[i]);
        vec.push_back(f[i] - mid);
    }

    mm.clear();
    sort(vec.begin(), vec.end()); mm[vec[0]] = ++cnt;
    for (int i = 1; i < vec.size(); i++) if (vec[i] > vec[i - 1]) mm[vec[i]] = ++cnt;

    fenw.update(mm[0], dp[0]); fenw2.update(mm[0], g[0]);
    for (int i = 1; i <= n; i++) {
        dp[i] = 1 + fenw.get(mm[f[i] - mid]); g[i] = 1 + fenw2.get(mm[f[i] - mid]);
        fenw.update(mm[f[i]], dp[i]); fenw2.update(mm[f[i]], g[i]);
    }

    return dp[n] <= k && k <= g[n];
}

int main(){
    //freopen("testgen.out", "r", stdin);
    //freopen("contestant.out", "w", stdout);
    //int t; scanf("%d", &t);
    //while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]), f[i] = f[i - 1] + a[i];

        long long l = -5e9, r = 5e9;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (check(mid)) r = mid - 1;
            else l = mid + 1;
        }

        printf("%lld", l);
    //}
    return 0;
}
/*
9 4
1 1 1 3 2 2 1 3 1
*/
