#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;

struct Point {
    int x, y;
    Point (int x = 0, int y = 0): x(x), y(y) {}
};

bool cmp (Point p1, Point p2) {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

long long cross (Point O, Point A, Point B) {
    return 1LL * (A.x - O.x) * (B.y - O.y) - 1LL * (A.y - O.y) * (B.x - O.x);
}

int n;
vector <Point> red, blue;

vector <Point> convexHull (vector <Point> polygon) {
    int n = (int)polygon.size();
    if (n <= 2) return polygon;

    sort(polygon.begin(), polygon.end(), cmp);

    vector <Point> hull, up, down;
    up.push_back(polygon[0]);
    down.push_back(polygon[0]);

    for (int i = 1; i < n; i++) {
        while (up.size() >= 2 && cross(up[up.size() - 2], up[up.size() - 1], polygon[i]) >= 0)
            up.pop_back();
        up.push_back(polygon[i]);

        while (down.size() >= 2 && cross(down[down.size() - 2], down[down.size() - 1], polygon[i]) <= 0)
            down.pop_back();
        down.push_back(polygon[i]);
    }

    for (int i = 0; i < up.size(); i++) hull.push_back(up[i]);
    for (int i = (int)down.size() - 2; i > 0; i--) hull.push_back(down[i]);
    return hull;
}

bool onSegment (Point P, Point A, Point B) {
    return cross(P, A, B) == 0 && P.x >= min(A.x, B.x) && P.x <= max(A.x, B.x) && P.y >= min(A.y, B.y) && P.y <= max(A.y, B.y);
}

bool isInsideTriangle (Point A, Point B, Point C, Point P) {
    long long s1 = abs(cross(A, B, C));
    long long s2 = abs(cross(P, A, B)) + abs(cross(P, B, C)) + abs(cross(P, C, A));

    if (s1 == 0 && s2 == 0) {
        return onSegment(P, A, B) || onSegment(P, A, C) || onSegment(P, B, C);
    }

    return s1 == s2;
}

bool isInsidePolygon (vector <Point> polygon, Point P) {
    int n = (int)polygon.size();
    int l = 1, r = n - 2;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (cross(polygon[0], P, polygon[mid]) > 0) l = mid + 1;
        else r = mid - 1;
    }

    return isInsideTriangle(polygon[0], polygon[r], polygon[r + 1], P);
}

int main(){
    freopen("curling.in", "r", stdin);
    freopen("curling.out", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        red.push_back(Point(x, y));
    }

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        blue.push_back(Point(x, y));
    }

    vector <Point> red_hull = convexHull(red);
    vector <Point> blue_hull = convexHull(blue);

    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < blue.size(); i++) ans1 += isInsidePolygon(red_hull, blue[i]);
    for (int i = 0; i < red.size(); i++) ans2 += isInsidePolygon(blue_hull, red[i]);
    cout << ans1 << " " << ans2 << "\n";
    return 0;
}
/*
5
0 0
0 2
0 4
0 6
0 8
0 1
0 3
0 5
0 7
0 9
*/
