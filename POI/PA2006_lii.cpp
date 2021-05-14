#include <bits/stdc++.h>

using namespace std;

unsigned long long n, p, e;
int k;

unsigned long long binPow (unsigned long long x, unsigned long long y) {
    unsigned long long ans = 1;
    while (y) {
        if (y & 1LLU) ans = (ans * x) % p;
        x = (x * x) % p;
        y >>= 1LLU;
    }
    return ans;
}

void input(){
    scanf("%llu %llu", &p, &e);
    scanf("%d", &k);
}

void solve(){
    while (k--) {
        scanf("%llu", &n);
        unsigned long long exp = (p - 1) / __gcd(e, p - 1);
        unsigned long long ans = binPow(n, exp);

        puts(ans == 1 ? "TAK" : "NIE");
    }
}

int main(){
    input();
    solve();
    return 0;
}
