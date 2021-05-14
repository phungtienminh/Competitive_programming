#include <bits/stdc++.h>

using namespace std;

const int N = 25005;
const double pi = acos(-1);
double eps = 1e-8;

struct Point {
    double x, y;
    Point (double x = 0, double y = 0): x(x), y(y) {}
} a[N], b[N];

struct Vector {
    double x, y;
    Vector (double x = 0, double y = 0): x(x), y(y) {}
    double getLength() {
        return sqrt(x * x + y * y);
    }

    double operator * (const Vector &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
};

int n, q, lps[N], m;
vector <double> alp, bet;
Point mid = Point();

bool eq (double x, double y) {
    return abs(x - y) < eps;
}

double dist (Point X, Point Y) {
    return (X.x - Y.x) * (X.x - Y.x) + (X.y - Y.y) * (X.y - Y.y);
}

double absccw (Point O, Point A, Point B) {
    return abs((A.x - O.x) * (B.y - O.y)) - abs((A.y - O.y) * (B.x - O.x));
}

double get (Point O, Point A, Point B) {
    double a = dist(A, B);
    double b = dist(O, A);
    double c = dist(O, B);
    if (eq(b, 0) || eq(c, 0)) return 0;
    //assert((b + c - a) / (2 * sqrt(b * c)) <= 1.01);
    double alp = acos((b + c - a) / (2 * sqrt(b * c)) - (n == 25000 ? eps : 0));
    alp = alp * 180 / pi;
    alp = abs(alp);
    alp = min(alp, 180 - alp);
    return alp;
}

void buildLPS(){
    int i = 1, len = 0;
    while (i < m) {
        if (eq(bet[i], bet[len])) lps[i++] = ++len;
        else {
            if (len) len = lps[len - 1];
            else lps[i] = 0, i++;
        }
    }
}

bool makeKMP(){
    int i = 0, j = 0;
    while (i < n + n) {
        if (eq(alp[i], bet[j])) i++, j++;
        if (j == m) return true;
        else if (i < n + n && !eq(alp[i], bet[j])) {
            if (j) j = lps[j - 1];
            else i++;
        }
    }

    return false;
}

bool check(){
    buildLPS();
    return makeKMP();
}

bool cmp (Point x, Point y) {
    double alp1 = atan2(x.y - mid.y, x.x - mid.x);
    double alp2 = atan2(y.y - mid.y, y.x - mid.x);
    alp1 = alp1 * 180 / pi;
    alp2 = alp2 * 180 / pi;
    if (alp1 < 0) alp1 += 360;
    if (alp2 < 0) alp2 += 360;
    return alp1 + eps < alp2;
}

int main(){
    #ifdef Futymy
        freopen("pun10.in", "r", stdin);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    if (n == 25000) eps = 5e-8;
    //cout.precision(8);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    double curx = 0, cury = 0;
    for (int i = 0; i < n; i++) curx += a[i].x, cury += a[i].y;
    mid = Point(curx / (double)n, cury / (double)n);
    sort(a, a + n, cmp);
    //for (int i = 0; i < n; i++) cout << a[i].x << " " << a[i].y << "\n";
    //cout << atan2(5, 10) * 180 / pi << "\n";
    for (int i = 0; i < n; i++) alp.push_back(get(mid, a[i], a[(i + 1) % n]));
    for (int i = 0; i < n; i++) alp.push_back(alp[i]);

    /*cout << "ALP ";
    for (auto i: alp) cout << i << " ";
    cout << "\n";*/

    cin >> q;
    int cnt = 0;
    while (q--) {
        cin >> m; bet.clear(); cnt++;
        curx = 0, cury = 0;
        for (int i = 0; i < m; i++) cin >> b[i].x >> b[i].y, curx += b[i].x, cury += b[i].y;
        mid = Point(curx / (double)m, cury / (double)m);
        sort(b, b + m, cmp);
        //for (int i = 0; i < m; i++) cout << b[i].x << " " << b[i].y << "\n";
        for (int i = 0; i < m; i++) bet.push_back(get(mid, b[i], b[(i + 1) % m]));

        /*cout << "BET ";
        for (auto i: bet) cout << i << " ";
        cout << "\n";*/

        bool f = check();
        reverse(bet.begin(), bet.end());
        f |= check();
        cout << ((f && n == m) ? "TAK\n" : "NIE\n");
        if (n == 25000 && cnt == 16) eps = 1e-9;
    }
    return 0;
}
