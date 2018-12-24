#include <bits/stdc++.h>

using namespace std;

const int N = 45;

int n;
long long a[N], m;
long long lef[1 << 20], rig[1 << 20], cntlef = 0, cntrig = 0;

int main(){
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i < (1 << (n / 2)); i++) {
        long long sum = 0;
        for (int j = 0; j < n / 2; j++) if (i & (1 << j)) sum += a[j + 1];
        lef[cntlef++] = sum;
    }

    for (int i = 0; i < (1 << (n - n / 2)); i++) {
        long long sum = 0;
        for (int j = 0; j < n - n / 2; j++) if (i & (1 << j)) sum += a[j + 1 + n / 2];
        rig[cntrig++] = sum;
    }

    sort(lef, lef + cntlef); sort(rig, rig + cntrig);
    long long ans = 0;
    for (int i = 0; i < cntlef; i++) ans += upper_bound(rig, rig + cntrig, m - lef[i]) - rig;
    printf("%lld", ans);
    return 0;
}
