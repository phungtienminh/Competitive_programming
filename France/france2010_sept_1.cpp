#include <bits/stdc++.h>

using namespace std;

int Maxx = -1e9, Maxy = -1e9, Miny = 1e9, Minx = 1e9, n, x = 0, y = 0;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int d, l;
        scanf("%d %d", &d, &l);
        if (d == 0) x -= l;
        if (d == 1) y += l;
        if (d == 2) x += l;
        if (d == 3) y -= l;

        Maxx = max(Maxx, x); Minx = min(Minx, x);
        Maxy = max(Maxy, y); Miny = min(Miny, y);
    }

    cout << (Maxy - Miny + Maxx - Minx) * 2 + 8;
    return 0;
}
