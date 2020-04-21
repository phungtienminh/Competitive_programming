#include <bits/stdc++.h>

using namespace std;

const int N = 25;

struct Cow {
    int height, weight, strength;
} a[N];

int n, h;

bool cmp (pair <int, int> p1, pair <int, int> p2) {
    return p1.first + p1.second > p2.first + p2.second;
}

int main(){
    #ifndef Futymy
        freopen("guard.in", "r", stdin);
        freopen("guard.out", "w", stdout);
    #endif // Futymy

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> h;
    for (int i = 0; i < n; i++) cin >> a[i].height >> a[i].weight >> a[i].strength;

    int ans = -1;
    for (int mask = 0; mask < (1 << n); mask++) {
        int totalh = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                totalh += a[i].height;
            }
        }

        if (totalh < h) continue;

        vector <pair <int, int> > vec;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                vec.push_back({a[i].weight, a[i].strength});
            }
        }

        sort(vec.begin(), vec.end(), cmp);
        int capacity = (int)1e9;
        bool ok = true;
        for (auto i: vec) {
            capacity = min(capacity - i.first, i.second);
            if (capacity < 0) ok = false;
        }

        if (ok) ans = max(ans, capacity);
    }

    if (ans == -1) cout << "Mark is too tall";
    else cout << ans;
    return 0;
}
