#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, x, a[N], f[N];
int bit[N];
long long ans = 0;

void update (int x) {
    for (int i = x; i < N; i += i & -i) bit[i]++;
}

int query (int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= i & -i) ans += bit[i];
    return ans;
}

int main(){
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), f[i] = f[i - 1] + (a[i] >= x ? 1 : -1);
    update(f[0] + 100005);
    for (int i = 1; i <= n; i++) {
        ans += query(f[i] + 100005);
        update(f[i] + 100005);
    }

    printf("%lld", ans);
    return 0;
}
