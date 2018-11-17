#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

struct Point {
    int x, y, id;

    bool operator < (const Point &rhs) const {
        return 1LL * x * rhs.y < 1LL * y * rhs.x;
    }
} a[N], b[N], c[N];

int n;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].x, &a[i].y), a[i].id = i;
    for (int i = 1; i <= n; i++) scanf("%d %d", &b[i].x, &b[i].y), b[i].id = i + n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c[j] = b[j];
            c[j].x -= a[i].x;
            c[j].y -= a[i].y;
            if (c[j].x == 0) c[j].y = 1;
            else if (c[j].y == 0) c[j].x = 1;
            else {
                if (c[j].y < 0) c[j].y = -c[j].y, c[j].x = -c[j].x;
                int cur = abs(__gcd(c[j].x, c[j].y));
                c[j].x /= cur;
                c[j].y /= cur;
            }
        }

        sort(c + 1, c + n + 1);
        for (int j = 2; j <= n; j++) if (c[j - 1].x == c[j].x && c[j - 1].y == c[j].y) return !printf("%d %d %d", a[i].id, c[j - 1].id, c[j].id);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c[j] = a[j];
            c[j].x -= b[i].x;
            c[j].y -= b[i].y;
            if (c[j].x == 0) c[j].y = 1;
            else if (c[j].y == 0) c[j].x = 1;
            else {
                if (c[j].y < 0) c[j].y = -c[j].y, c[j].x = -c[j].x;
                int cur = abs(__gcd(c[j].x, c[j].y));
                c[j].x /= cur;
                c[j].y /= cur;
            }
        }

        sort(c + 1, c + n + 1);
        for (int j = 2; j <= n; j++) if (c[j - 1].x == c[j].x && c[j - 1].y == c[j].y) return !printf("%d %d %d", c[j - 1].id, c[j].id, b[i].id);
    }

    printf("%d", -1);
    return 0;
}
