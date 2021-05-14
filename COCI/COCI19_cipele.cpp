#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, a[N], b[N];

bool check (int mid, bool small) {
    if (!small) {
        int pt = 1;
        for (int i = 1; i <= n; i++) {
            while (pt <= m && b[pt] < a[i] - mid) pt++;
            if (pt > m || b[pt] > a[i] + mid) return false;
            pt++;
        }
    }
    else {
        int pt = 1;
        for (int i = 1; i <= m; i++) {
            while (pt <= n && a[pt] < b[i] - mid) pt++;
            if (pt > n || a[pt] > b[i] + mid) return false;
            pt++;
        }
    }

    return true;
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
    sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);

    if (n <= m) {
        int l = 0, r = 1e9;
        while (l <= r) {
            int mid = (l + r) / 2;

            if (check(mid, 0)) r = mid - 1;
            else l = mid + 1;
        }

        printf("%d", l);
    }
    else {
        int l = 0, r = 1e9;
        while (l <= r) {
            int mid = (l + r) / 2;

            if (check(mid, 1)) r = mid - 1;
            else l = mid + 1;
        }

        printf("%d", l);
    }
    return 0;
}
