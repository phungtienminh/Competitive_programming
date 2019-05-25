#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
const long long inf = 1e18 + 205;

int n;
long long a, b, l[N], r[N], sum = 0, ans = 0;
vector <pair <long long, long long> > vec;

pair <long long, long long> calc (long long t) {
    return {(t + t / b) % a, t % b};
}

int main(){
    scanf("%d %lld %lld", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &l[i], &r[i]);
        sum += r[i] - l[i] + 1;
    }

    long long g = __gcd(a, b + 1);
    a /= g;
    if (a > inf / b) return !printf("%lld", sum);
    long long mod = a * b;

    for (int i = 1; i <= n; i++) {
        if (l[i] / mod + 1 < r[i] / mod) return !printf("%lld", mod);
        if (l[i] / mod == r[i] / mod) vec.push_back({l[i] % mod, r[i] % mod});
        if (l[i] / mod + 1 == r[i] / mod) {
            vec.push_back({l[i] % mod, mod - 1});
            vec.push_back({0LL, r[i] % mod});
        }
    }

    sort(vec.begin(), vec.end());
    long long sta = vec[0].first, fin = vec[0].second;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i].first <= fin) fin = max(fin, vec[i].second);
        else {
            ans += fin - sta + 1;
            sta = vec[i].first; fin = vec[i].second;
        }
    }

    ans += fin - sta + 1;
    printf("%lld", ans);
    return 0;
}
