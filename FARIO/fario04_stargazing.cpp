#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point &other) const {
        if (y != other.y) return y < other.y;
        return x < other.x;
    }
};

int main(){
    int n;
    scanf("%d", &n);
    Point a[n];
    for (int i = 0; i<n; ++i) scanf("%d %d", &a[i].x, &a[i].y);
    sort(a, a+n);

    int ans = 0;
    int l = 0;
    int r = 0;
    int k = n - 1;

    while (l < n) {
        while (a[r].y == a[l].y) r++;
        for (int i = l + 1; i<r; i++) {
            int temp = a[i].x - a[l].x;
            int other = a[l].y - temp;

            while (a[k].y > other) k--;
            for (int j = k; j>=0; j--) {
                if (a[l].x < a[j].x && a[j].x < a[i].x) ans = max(ans, a[i].x - a[l].x + a[l].y - a[j].y);
            }
        }
        k = n - 1;
        l++;
    }
    printf("%d", ans);
    return 0;
}
