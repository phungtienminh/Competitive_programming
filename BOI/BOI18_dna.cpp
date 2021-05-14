#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, k, r, a[N], need[N], cnt[N];

bool check (int mid) {
    int res = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= mid; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] == need[a[i]]) res++;
    }

    if (res == r) return true;

    int cur = mid;
    while (cur < n) {
        cur++;
        cnt[a[cur]]++;
        if (cnt[a[cur]] == need[a[cur]]) res++;
        if (cnt[a[cur - mid]] == need[a[cur - mid]]) res--;
        cnt[a[cur - mid]]--;
        if (res == r) return true;
    }

    return false;
}

int main(){
    scanf("%d %d %d", &n, &k, &r);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= r; i++) {
        int type, x;
        scanf("%d %d", &type, &x);
        need[type] = x;
    }

    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid - 1;
        else l = mid + 1;
    }

    if (l > n) printf("impossible");
    else printf("%d", l);
    return 0;
}
