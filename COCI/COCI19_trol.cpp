#include <bits/stdc++.h>

using namespace std;

int q;
long long l, r;

int main(){
    scanf("%d", &q);
    while (q--) {
        scanf("%lld %lld", &l, &r);
        long long ans = 0;

        for (int i = 0; i < 9; i++) {
            long long templ = l, tempr = r;
            while (templ % 9 != i) templ++;
            while (tempr % 9 != i && tempr > 0) tempr--;

            if (templ > tempr) continue;
            long long res = (tempr - templ + 1) / 9 + 1;
            if (i) ans += res * (long long)i;
            else ans += res * 9LL;
        }

        printf("%lld\n", ans);
    }
    return 0;
}
