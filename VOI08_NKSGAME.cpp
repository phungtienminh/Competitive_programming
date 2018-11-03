#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], b[N], ans = 2e9;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);

    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(b + 1, b + n + 1, -a[i]) - b;
        if (pos == 1) ans = min(ans, abs(a[i] + b[pos]));
        else ans = min(ans, min(abs(a[i] + b[pos]), abs(a[i] + b[pos - 1])));
    }

    printf("%d", ans);
    return 0;
}
