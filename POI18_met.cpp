#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

vector <int> pos[N];
int need[N], a[N], lef[N], rig[N], s[N], e[N], n, k, q;
long long tree[N];

void input(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; i++) {
        int x;
        scanf("%d", &x);
        pos[x].push_back(i);
    }

    for (int i = 1; i <= n; i++) scanf("%d", &need[i]);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) scanf("%d %d %d", &lef[i], &rig[i], &a[i]);
    for (int i = 1; i <= n; i++) {
        s[i] = 1;
        e[i] = q + 1;
    }
}

void modify (int x, int val) {
    while (x <= k) {
        tree[x] += val;
        x += x & -x;
    }
}

long long query (int x) {
    long long ans = 0;
    while (x > 0) {
        ans += tree[x];
        x -= x & -x;
    }

    return ans;
}

void solve(){
    while (1) {
        memset(tree, 0, sizeof(tree));
        vector <pair <int, int> > all;
        for (int i = 1; i <= n; i++) if (s[i] != e[i]) all.push_back(make_pair((s[i] + e[i]) / 2, i));

        if (all.size() == 0) break;

        sort(all.begin(), all.end());
        int pt = 0;
        for (int i = 1; i <= q; i++) {
            if (lef[i] <= rig[i]) {
                modify(lef[i], a[i]);
                modify(rig[i] + 1, -a[i]);
            }
            else {
                modify(lef[i], a[i]);
                modify(1, a[i]);
                modify(rig[i] + 1, -a[i]);
            }


            while (pt < all.size() && all[pt].first == i) {
                long long cur = 0;
                for (auto j: pos[all[pt].second]) {
                    cur += query(j);
                    cur = min(cur, (long long)1e18);
                }

                if (cur < need[all[pt].second]) s[all[pt].second] = all[pt].first + 1;
                else e[all[pt].second] = all[pt].first;

                pt++;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (s[i] > q) puts("NIE");
        else printf("%d\n", s[i]);
    }
}

int main(){
    input();
    solve();
    return 0;
}
