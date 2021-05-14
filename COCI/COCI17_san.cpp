#include <bits/stdc++.h>

using namespace std;

const int N = 45;
const int maxn = 21e5 + 5;

int n, h[N], g[N], bit[maxn], cnt = 0;
long long k;
vector <pair <long long, int> > vec1, vec2;
vector <int> vec;
map <int, int> mm;

void update (int x) {
    for (int i = x; i > 0; i -= i & -i) bit[i]++;
}

int query (int x) {
    int ans = 0;
    for (int i = x; i < maxn; i += i & -i) ans += bit[i];
    return ans;
}

int main(){
    scanf("%d %lld", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d %d", &h[i], &g[i]);
    for (int mask = 0; mask < (1 << (n / 2)); mask++) {
        long long total = 0;
        int curh = 0;
        bool ok = true;

        for (int i = 0; i < n / 2; i++) {
            if (mask & (1 << i)) {
                if (h[i] < curh) {
                    ok = false;
                    break;
                }

                curh = h[i];
                total += g[i];
            }
        }

        if (ok) vec1.push_back({total, curh});
        vec.push_back(curh);
    }

    for (int mask = 0; mask < (1 << (n - n / 2)); mask++) {
        long long total = 0;
        int curh = 0, curh2 = 0;
        bool ok = true;

        for (int i = 0; i < n - n / 2; i++) {
            if (mask & (1 << i)) {
                if (h[i + n / 2] < curh) {
                    ok = false;
                    break;
                }

                curh = h[i + n / 2];
                if (!curh2) curh2 = h[i + n / 2];
                total += g[i + n / 2];
            }
        }

        if (curh2 == 0) curh2 = 1e9;
        if (ok) vec2.push_back({total, curh2});
        vec.push_back(curh2);
    }

    sort(vec.begin(), vec.end()); mm[vec[0]] = ++cnt;
    for (int i = 1; i < vec.size(); i++) if (vec[i] > vec[i - 1]) mm[vec[i]] = ++cnt;

    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());
    int ptr = vec2.size() - 1;

    //for (auto i: vec1) cout << i.first << " " << i.second << "\n";
    //cout << '\n';
    //for (auto i: vec2) cout << i.first << " " << i.second << '\n';

    long long ans = 0;
    for (int i = 0; i < vec1.size(); i++) {
        while (ptr >= 0 && vec1[i].first + vec2[ptr].first >= k) {
            update(mm[vec2[ptr].second]);
            ptr--;
        }

        ans += query(mm[vec1[i].second]);
    }

    printf("%lld", ans);
    return 0;
}
