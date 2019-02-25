#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int inf = 1e9 + 2277;

struct Point {
    int x, y, type, id;
    bool operator < (const Point &rhs) const {
        return x < rhs.x || (x == rhs.x && y > rhs.y);
    }
} a[N];

set <pair <int, pair <int, int> > > S;
int n, res[N];
long long ans = 0;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].x, &a[i].y), a[i].id = i, a[i].type = 1;
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i + n].x, &a[i + n].y), a[i + n].id = i, a[i + n].type = 0;
    sort(a + 1, a + n + n + 1);
    for (int i = 1; i <= n + n; i++) {
        //cout << a[i].x << " " << a[i].y << " " << a[i].type << "\n";
        if (a[i].type) S.insert({a[i].y, {a[i].x, a[i].id}});
        else {
            auto it = S.lower_bound({a[i].y, {-1e9, -1e9}});
            ans += abs(a[i].x - (*it).second.first) + abs(a[i].y - (*it).first);
            res[(*it).second.second] = a[i].id;
            S.erase(it);
            //cout << i << " " << (*it).second.second << " " << a[i].id << "\n";
        }
    }

    printf("%lld\n", ans);
    for (int i = 1; i <= n; i++) printf("%d %d\n", i, res[i]);
    return 0;
}
