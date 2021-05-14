#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;
int a[N], pref[N], n;

int main(){
    scanf("%d", &n);
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pref[i] = pref[i - 1] + a[i];
    }

    int ans = 0;
    int l = 1;
    int r = 1;

    while (l <= n) {
        while (1) {
            int dist = abs(pref[r - 1] - pref[l - 1]);
            if (r < l) dist = pref[n] - dist;

            ans = max(ans, min(dist, pref[n] - dist));
            if (dist > pref[n] - dist) break;
            ans = max(ans, dist);
            r = r % n + 1;
            if (r == l) break;
        }

        l++;
    }

    printf("%d", ans);
    return 0;
}
