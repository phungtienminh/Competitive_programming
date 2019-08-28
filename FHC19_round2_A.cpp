#include <bits/stdc++.h>

using namespace std;

int t, n, m, k, x, y, xa, ya, xb, yb;

void solve (int Test) {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &x, &y);
    if (k == 1) scanf("%d %d", &xa, &ya);
    else scanf("%d %d %d %d", &xa, &ya, &xb, &yb);

    if (k == 1) printf("Case #%d: N\n", Test);
    else {
        int d1 = abs(x - xa) + abs(y - ya);
        int d2 = abs(x - xb) + abs(y - yb);
        if (d1 % 2 == 1 && d2 % 2 == 1) printf("Case #%d: N\n", Test);
        else {
            int d = abs(xa - xb) + abs(ya - yb);
            if (d % 2 == 0) printf("Case #%d: Y\n", Test);
            else printf("Case #%d: N\n", Test);
        }
    }
}

int main(){
    //freopen("on_the_run.txt", "r", stdin);
    //freopen("contestant.out", "w", stdout);
    scanf("%d", &t);
    for (int T = 1; T <= t; T++) solve(T);
    return 0;
}
