#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int d[N][N], a, b, c, need, sum;

struct Tracing {
    int from, to, nfrom, nto;
    Tracing (int from = 0, int to = 0, int nfrom = 0, int nto = 0): from(from), to(to), nfrom(nfrom), nto(nto) {}
} trace[N][N];

void bfs(){
    memset(d, 0x3f, sizeof(d)); d[a][0] = 0;
    queue <pair <int, int> > q; q.push({a, 0});
    while (!q.empty()) {
        int ca = q.front().first, cb = q.front().second, cc = sum - ca - cb; q.pop();
        if (ca == need || cb == need || cc == need) {
            vector <pair <int, int> > ans;
            int cura = ca, curb = cb;
            while (!(cura == a && curb == 0)) {
                ans.push_back({trace[cura][curb].from, trace[cura][curb].to});
                int nfrom = trace[cura][curb].nfrom, nto = trace[cura][curb].nto;
                cura += nfrom; curb -= nto;
            }

            reverse(ans.begin(), ans.end());
            for (auto i: ans) printf("%d %d\n", i.first, i.second);

            if (ca == need) printf("0 %d", 1);
            else if (cb == need) printf("0 %d", 2);
            else printf("0 %d", 3);
            return;
        }

        //Pour 1 to 2
        int trans = min(ca, b - cb);
        if (d[ca - trans][cb + trans] > d[ca][cb] + 1) {
            d[ca - trans][cb + trans] = d[ca][cb] + 1;
            trace[ca - trans][cb + trans] = Tracing(1, 2, trans, trans);
            q.push({ca - trans, cb + trans});
        }

        //Pour 1 to 3
        trans = min(ca, c - cc);
        if (d[ca - trans][cb] > d[ca][cb] + 1) {
            d[ca - trans][cb] = d[ca][cb] + 1;
            trace[ca - trans][cb] = Tracing(1, 3, trans, 0);
            q.push({ca - trans, cb});
        }

        //Pour 2 to 1
        trans = min(cb, a - ca);
        if (d[ca + trans][cb - trans] > d[ca][cb] + 1) {
            d[ca + trans][cb - trans] = d[ca][cb] + 1;
            trace[ca + trans][cb - trans] = Tracing(2, 1, -trans, -trans);
            q.push({ca + trans, cb - trans});
        }

        //Pour 2 to 3
        trans = min(cb, c - cc);
        if (d[ca][cb - trans] > d[ca][cb] + 1) {
            d[ca][cb - trans] = d[ca][cb] + 1;
            trace[ca][cb - trans] = Tracing(2, 3, 0, -trans);
            q.push({ca, cb - trans});
        }

        //Pour 3 to 1
        trans = min(cc, a - ca);
        if (d[ca + trans][cb] > d[ca][cb] + 1) {
            d[ca + trans][cb] = d[ca][cb] + 1;
            trace[ca + trans][cb] = Tracing(3, 1, -trans, 0);
            q.push({ca + trans, cb});
        }

        //Pour 3 to 2
        trans = min(cc, b - cb);
        if (d[ca][cb + trans] > d[ca][cb] + 1) {
            d[ca][cb + trans] = d[ca][cb] + 1;
            trace[ca][cb + trans] = Tracing(3, 2, 0, trans);
            q.push({ca, cb + trans});
        }
    }

    printf("0 0");
}

int main(){
    #ifndef Futymy
        freopen("jugsin.txt", "r", stdin);
        freopen("jugsout.txt", "w", stdout);
    #endif // Futymy
    scanf("%d %d %d %d", &a, &b, &c, &need); sum = a;
    bfs();
    return 0;
}
