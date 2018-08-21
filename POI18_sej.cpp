#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 250005;
int a[N], n, k;
vector <int> dvs, prime;
set <int> st;

void sieve(){
    int m = n;
    dvs.push_back(1);
    for (int i = 2; i < sqrt(n); i++) {
        if (n % i == 0) {
            dvs.push_back(i);
            if (m % i == 0) {
                prime.push_back(i);
                while (m % i == 0) m /= i;
            }
        }
    }

    if ((int)sqrt(n) * (int)sqrt(n) == n) dvs.push_back(sqrt(n));
    for (int i = dvs.size() - 1; i >= 0; i--) dvs.push_back(n / dvs[i]);
}

signed main(){
    scanf("%lld %lld", &n, &k);
    for (int i = 1; i <= k; i++) scanf("%lld", &a[i]);
    sieve();

    int ans = 0;
    for (int i = 1; i <= k - 1; i++) a[i] = __gcd(n, a[i]);
    for (int i = 1; i <= k - 1; i++) st.insert(a[i]);

    //for (int i = 1; i <=k - 1; i++) cout << a[i] << " ";
    //cout << "\n";
    for (int i = dvs.size() - 1; i >= 0; i--) {
        if (st.find(dvs[i]) != st.end()) {
            for (int j = 0; j < prime.size(); j++) if (dvs[i] % prime[j] == 0) st.insert(dvs[i] / prime[j]);
        }
        else if (a[k] % dvs[i] == 0) ans = max(ans, n / dvs[i]);
    }

    printf("%lld", ans);
    return 0;
}
