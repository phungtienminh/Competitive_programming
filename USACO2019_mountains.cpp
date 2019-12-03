#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, bit[N], cnt = 0;
pair <int, int> p[N];
map <int, int> bijection;
vector <int> vec;

void update (int pos) {
    for (int i = pos; i < N; i += i & -i) bit[i]++;
}

int query (int pos) {
    int ans = 0;
    for (int i = pos; i > 0; i -= i & -i) ans += bit[i];
    return ans;
}

bool cmp (pair <int, int> p1, pair <int, int> p2) {
    if (p1.first != p2.first) return p1.first > p2.first;
    return p1.second < p2.second;
}

int main(){
    #ifndef Futymy
        freopen("mountains.in", "r", stdin);
        freopen("mountains.out", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        p[i] = {a + b, a - b};
        vec.push_back(a - b);
    }

    sort(vec.begin(), vec.end());
    bijection[vec[0]] = ++cnt;
    for (int i = 1; i < vec.size(); i++) if (vec[i] > vec[i - 1]) bijection[vec[i]] = ++cnt;
    for (int i = 1; i <= n; i++) p[i].second = bijection[p[i].second];

    sort(p + 1, p + n + 1, cmp);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (query(p[i].second) == 0);
        update(p[i].second);
    }

    printf("%d", ans);
    return 0;
}
