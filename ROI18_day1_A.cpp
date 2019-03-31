#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, q, row[N], col[N], ans = 0, onrow[N], oncol[N];
vector <vector <int> > a;

int main(){
    scanf("%d %d %d", &n, &m, &q);
    a.assign(n + 1, vector <int>(m + 1, 0));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) row[i] = max(row[i], a[i][j]), col[j] = max(col[j], a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] == row[i] && a[i][j] == col[j]) onrow[i] = j, oncol[j] = i, ans++;

    //Process queries.
    while (q--) {
        int x, y, val;
        scanf("%d %d %d", &x, &y, &val);
        if (row[x] < val && onrow[x]) oncol[onrow[x]] = 0, onrow[x] = 0, ans--;
        if (col[y] < val && oncol[y]) onrow[oncol[y]] = 0, oncol[y] = 0, ans--;
        row[x] = max(row[x], val); col[y] = max(col[y], val);
        if (!onrow[x] && !oncol[y] && row[x] == val && col[y] == val) ans++, onrow[x] = y, oncol[y] = x;
        a[x][y] = val;
        printf("%d\n", ans);

        //cout << "=======\n";
        //for (int i = 1; i <= n; i++) cout << onrow[i] << '\n';
        //for (int i = 1; i <= m; i++) cout << oncol[i] << "\n";
    }
    return 0;
}
