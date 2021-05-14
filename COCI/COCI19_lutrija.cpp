#include <bits/stdc++.h>

using namespace std;

vector <long long> ans;
long long a, b;

bool check (long long x) {
    if (x < 2) return false;
    if (x < 4) return true;
    for (int i = 2; 1LL * i * i <= x; i++) if (x % i == 0) return false;
    return true;
}

void solve2 (int type) {
    if (type) {
        ans.clear();
        ans.push_back(a);
    }

    if (a == 2) {
        vector <long long> pot; pot.push_back(b);
        for (int i = 2; ; i += 2) {
            if (check(b - i)) pot.push_back(b - i);
            else break;
        }

        for (int i = 2; ; i += 2) {
            if (check(b + i)) pot.push_back(b + i);
            else break;
        }

        for (auto i: pot) {
            if (check(i - a)) {
                if (i < b) {
                    for (long long j = i; j <= b; j += 2) ans.push_back(j);
                }
                else {
                    for (long long j = i; j >= b; j -= 2) ans.push_back(j);
                }

                if (type) reverse(ans.begin(), ans.end());
                printf("%d\n", (int)ans.size());
                for (auto i: ans) printf("%lld ", i);
                return;
            }
        }

        printf("%d", -1);
    }
    else {
        swap(a, b);
        solve2(1);
    }
}

void solve3(){
    ans.clear();
    vector <long long> pot1, pot2;

    pot1.push_back(a);
    for (int i = 2; ; i += 2) {
        if (check(a + i)) pot1.push_back(a + i);
        else break;
    }

    for (int i = 2; ; i += 2) {
        if (check(a - i)) pot1.push_back(a - i);
        else break;
    }

    pot2.push_back(b);
    for (int i = 2; ; i += 2) {
        if (check(b + i)) pot2.push_back(b + i);
        else break;
    }

    for (int i = 2; ; i += 2) {
        if (check(b - i)) pot2.push_back(b - i);
        else break;
    }

    long long pos1 = 0, pos2 = 0;
    for (auto i: pot1) {
        if (check(i - 2)) {
            pos1 = i;
            break;
        }
    }

    for (auto i: pot2) {
        if (check(i - 2)) {
            pos2 = i;
            break;
        }
    }

    if (!pos1 || !pos2) {
        printf("%d", -1);
        return;
    }

    if (a < pos1) {
        for (long long i = a; i <= pos1; i += 2) ans.push_back(i);
    }
    else {
        for (long long i = a; i >= pos1; i -= 2) ans.push_back(i);
    }

    ans.push_back(2);
    if (pos2 > b) {
        for (long long i = pos2; i >= b; i -= 2) ans.push_back(i);
    }
    else {
        for (long long i = pos2; i <= b; i += 2) ans.push_back(i);
    }

    printf("%d\n", (int)ans.size());
    for (auto i: ans) printf("%lld ", i);
}

void solve1(){
    long long ini = a;
    if (a < b) {
        while (a <= b - 2) {
            a += 2;
            if (!check(a)) break;
            ans.push_back(a);
        }

        if (a <= b - 2) {
            if (!check(ini - 2)) {
                a = ini; solve3();
                return;
            }

            ans.clear(); ans.push_back(ini); ans.push_back(2);
            a = 2;
            solve2(0);
            return;
        }
        else {
            printf("%d\n", (int)ans.size());
            for (auto i: ans) printf("%lld ", i);
        }
    }
    else {
        while (a >= b + 2) {
            a -= 2;
            if (!check(a)) break;
            ans.push_back(a);
        }

        if (a >= b + 2) {
            if (!check(ini - 2)) {
                a = ini; solve3();
                return;
            }

            ans.clear(); ans.push_back(ini); ans.push_back(2);
            a = 2;
            solve2(0);
            return;
        }
        else {
            printf("%d\n", (int)ans.size());
            for (auto i: ans) printf("%lld ", i);
        }
    }
}

int main(){
    scanf("%lld %lld", &a, &b); ans.push_back(a);
    if (a != 2 && b != 2) solve1();
    else solve2(a == 2 ? 0 : 1);
    return 0;
}
