#include <bits/stdc++.h>

using namespace std;

const int N = 5;
const int maxn = 3e4 + 5;

int m, n, x, y;

struct Rect {
    int x, x2, y, y2;
} a[N];

void update (int &x, int &y, int x2, int y2) {
    x = max(x, x2);
    y = max(y, y2);
}

void update2 (int &x, int &y, int x2, int y2) {
    x = min(x, x2);
    y = min(y, y2);
}

int solve (vector <Rect> vec) {
    int Maxx = -1e9, Maxy = -1e9, Minx = 1e9, Miny = 1e9;
    for (auto i: vec) update(Maxx, Maxy, i.x, i.y), update2(Minx, Miny, i.x2, i.y2);
    return max(0, Minx - Maxx + 1) * max(0, Miny - Maxy + 1);
}

int main(){
    #ifndef Futymy
        freopen("mallsin.txt", "r", stdin);
        freopen("mallsout.txt", "w", stdout);
    #endif // Futymy
    scanf("%d %d %d %d", &m, &n, &x, &y);
    for (int i = 1; i <= 4; i++) {
        scanf("%d %d", &a[i].y2, &a[i].x2);
        a[i].x2++; a[i].y2++;
        a[i].x = max(1, a[i].x2 - y + 1); a[i].y = max(1, a[i].y2 - x + 1);
        a[i].x2 = min(a[i].x2, n - y + 1); a[i].y2 = min(a[i].y2, m - x + 1);
        //swap(a[i].x, a[i].y); swap(a[i].x2, a[i].y2);
    }

    int ans = (m - x + 1) * (n - y + 1);
    for (int mask = 1; mask < (1 << 4); mask++) {
        vector <Rect> vec;
        for (int i = 0; i < 4; i++) {
            if (mask & (1 << i)) vec.push_back(a[i + 1]);
        }

        if (__builtin_popcount(mask) % 2 == 1) ans -= solve(vec);
        else ans += solve(vec);
        //cout << ans << "\n";
        //if (mask == 3) break;
        //break;
    }

    //ans = max(ans, 0);
    printf("%d", ans);
    return 0;
}
/*
6 4 3 3
0 1
2 2
4 1
4 2
*/
