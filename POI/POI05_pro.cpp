#include <bits/stdc++.h>

using namespace std;

const int N = 7005;

struct Point {
    int x, y;
};

struct Rect {
    Point ll, ur, lr, ul;
} a[N];

int n;

bool isOverlap (Rect x, Rect y) {
    if (x.ur.x < y.ul.x || x.ul.x > y.ur.x) return false;
    if (x.ur.y < y.lr.y || x.lr.y > y.ur.y) return false;
    return true;
}

struct disj {
    int par[N], ndsu;
    void init (int n) {
        for (int i = 1; i <= n; i++) par[i] = i;
        ndsu = n;
    }

    int Find (int x) {
        return par[x] == x ? x : par[x] = Find(par[x]);
    }

    void join (int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;
        par[y] = x; ndsu--;
    }
} dsu;

bool same (Point x, Point y) {
    return x.x == y.x && x.y == y.y;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d %d %d", &a[i].ll.x, &a[i].ll.y, &a[i].ur.x, &a[i].ur.y);
    for (int i = 1; i <= n; i++) {
        a[i].ul.x = a[i].ll.x;
        a[i].ul.y = a[i].ur.y;
        a[i].lr.x = a[i].ur.x;
        a[i].lr.y = a[i].ll.y;
    }

    dsu.init(n);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int cnt = 0;
            if (same(a[i].ur, a[j].ll)) cnt++;
            if (same(a[i].ul, a[j].lr)) cnt++;
            if (same(a[i].ll, a[j].ur)) cnt++;
            if (same(a[i].lr, a[j].ul)) cnt++;
            if (isOverlap(a[i], a[j]) && cnt != 1) dsu.join(i, j);
        }
    }

    printf("%d", dsu.ndsu);
    return 0;
}
