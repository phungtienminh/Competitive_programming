#include <bits/stdc++.h>

using namespace std;

map <long long, int> mm;
vector <long long> have[10];

int n, k;
long long x;

void input(){
    cin >> k >> n;
}

void solve(){
    long long cur = 0;
    for (int i = 1; i <= 8; i++) {
        cur = cur * 10 + k;
        mm[cur] = i;
        have[i].push_back(cur);
    }

    for (int i = 2; i <= 8; i++) {
        for (int j = 1; j * 2 <= i; j++) {
            for (long long u: have[j]) {
                for (long long v: have[i - j]) {
                    if (!mm.count(u + v)) {
                        mm[u + v] = i;
                        have[i].push_back(u + v);
                    }
                    if (u > v && !mm.count(u - v)) {
                        mm[u - v] = i;
                        have[i].push_back(u - v);
                    }
                    if (v > u && !mm.count(v - u)) {
                        mm[v - u] = i;
                        have[i].push_back(v - u);
                    }
                    if (!mm.count(u * v)) {
                        mm[u * v] = i;
                        have[i].push_back(u * v);
                    }
                    if (u % v == 0 && !mm.count(u / v)) {
                        mm[u / v] = i;
                        have[i].push_back(u / v);
                    }
                    if (v % u == 0 && !mm.count(v / u)) {
                        mm[v / u] = i;
                        have[i].push_back(v / u);
                    }
                }
            }
        }
    }

    while (n--) {
        cin >> x;
        if (mm.count(x)) cout << mm[x] << "\n";
        else cout << "NIE\n";
    }
}

int main(){
    input();
    solve();
    return 0;
}
