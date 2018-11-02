#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, a[N];

bool check (int x) {
    int cur = sqrt(x * 2);
    return cur * (cur + 1) == x * 2;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int ans = 0, l = 1, r = 1;

    while (l <= n) {
        while (l <= n && !check(a[l])) l++;
        if (l > n) break;
        r = l + 1;
        while (r <= n && a[r] >= a[r - 1] && check(a[r])) r++;
        ans = max(ans, r - l); l = r;
    }

    printf("%d", ans);
    return 0;
}
