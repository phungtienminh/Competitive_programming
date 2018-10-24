#include <bits/stdc++.h>

using namespace std;

int primes[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

long long n;
vector <pair <long long, long long> > vec;

bool cmp (pair <long long, long long> p1, pair <long long, long long> p2) {
    return (p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second));
}

void bt (int pos, long long dvs, long long lim, long long num) {
    if (pos == 15) return;

    long long res = num, Pow = 0;
    for (int i = 1; i <= lim; i++) {
        if (res > n / primes[pos]) break;
        res *= primes[pos]; Pow++;
        vec.push_back({dvs * (Pow + 1), res});
        bt(pos + 1, dvs * (Pow + 1), Pow, res);
    }
}

int main(){
    scanf("%lld", &n);
    vec.push_back({1, 1});
    bt(0, 1, 60, 1);
    sort(vec.begin(), vec.end(), cmp);
    printf("%lld", vec[0].second);
    return 0;
}
