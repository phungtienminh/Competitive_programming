#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;

int n, m, a[N], b[N];

void input(){
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%lld", &b[i]);
    sort(b + 1, b + m + 1);
}

bool check (int mid) {
    priority_queue <int> pq;
    for (int i = 1; i <= n; i++) pq.push(a[i]);
    for (int i = mid; i >= 1; i--) {
        if (pq.top() < b[i]) return false;

        int val = pq.top(); pq.pop();
        pq.push(val - b[i]);
    }

    return true;
}

void solve(){
    int l = 1;
    int r = m;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }

    printf("%lld", r);
}

signed main(){
    input();
    solve();
    return 0;
}
