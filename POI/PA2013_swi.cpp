#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct data {
    double x, y, a, b;
} a[N];

int n;

double f (double mid) {
    double Maxx = -1e18, Maxy = -1e18, Minx = 1e18, Miny = 1e18;
    for (int i = 1; i <= n; i++) {
        Maxx = max(Maxx, a[i].x + a[i].a * mid);
        Minx = min(Minx, a[i].x + a[i].a * mid);
        Maxy = max(Maxy, a[i].y + a[i].b * mid);
        Miny = min(Miny, a[i].y + a[i].b * mid);
    }

    return max(Maxx - Minx, Maxy - Miny);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y >> a[i].a >> a[i].b;

    double l = 0, r = 1e9;
    for (int i = 1; i <= 300; i++) {
        double mid1 = l + (r - l) / 3;
        double mid2 = r - (r - l) / 3;
        if (f(mid1) < f(mid2)) r = mid2;
        else l = mid1;
    }

    cout << fixed << setprecision(10) << f(l);
    return 0;
}
