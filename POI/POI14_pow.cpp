#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

class Data {
public:
    int fi, sefi, sese;

    Data (int fi, int sefi, int sese) {
        this->fi = fi;
        this->sefi = sefi;
        this->sese = sese;
    }

    bool operator<(const Data &other) const {
        return fi < other.fi;
    }
};

int par[N * N], pumped[N * N], n, m, a[N][N];

vector <pair <int, int> > byteburg;
vector <Data> cells;

void init (int n) {
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        pumped[i] = 0;
    }
}

int Find (int x) {
    return (par[x] == x ? x : par[x] = Find(par[x]));
}

void join (int x, int y) {
    x = Find(x); y = Find(y);
    if (x == y) return;

    pumped[x] |= pumped[y];
    par[y] = x;
}

void input(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}

void solve(){
    init(n * m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] > 0) byteburg.push_back(make_pair(a[i][j], (i - 1) * m + j));
            else a[i][j] = -a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i < n) cells.push_back(Data(max(a[i][j], a[i + 1][j]), (i - 1) * m + j, i * m + j));
            if (j < m) cells.push_back(Data(max(a[i][j], a[i][j + 1]), (i - 1) * m + j, (i - 1) * m + j + 1));
        }
    }

    sort(byteburg.begin(), byteburg.end());
    sort(cells.begin(), cells.end());

    int ans = 0;
    int ptr = 0;

    for (int i = 0; i < byteburg.size(); i++) {
        while (ptr < cells.size() && cells[ptr].fi <= byteburg[i].first) {
            join(cells[ptr].sefi, cells[ptr].sese);
            ptr++;
        }

        if (!pumped[Find(byteburg[i].second)]) {
            ans++;
            pumped[Find(byteburg[i].second)] = 1;
        }
    }

    printf("%d", ans);
}

int main(){
    input();
    solve();
    return 0;
}
