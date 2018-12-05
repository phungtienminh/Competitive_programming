#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, x, y, s;
char a[N][N];
map <pair <int, pair <int, int> >, int> mm;

bool inside (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int main(){
    #ifndef Futymy
        freopen("robot.inp", "r", stdin);
        freopen("robot.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> x >> y >> s;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
    mm[{0, {y, x}}] = 0;

    int cur = 0, curx = y, cury = x, curs = 0;
    bool f = false;
    if (curx > n + 1) {
        int need = curx - (n + 1);
        need = min(need, s);
        s -= need; curx -= need;
    }
    while (inside(curx + dx[curs], cury + dy[curs]) && a[curx + dx[curs]][cury + dy[curs]] == '#') curs = (curs + 1) % 4;
    while (cur < s) {
        cur++;
        curx += dx[curs]; cury += dy[curs];
        while (inside(curx + dx[curs], cury + dy[curs]) && a[curx + dx[curs]][cury + dy[curs]] == '#') curs = (curs + 1) % 4;
        if (cury > n) {
            if (curs != 1) return cout << cury + (s - cur) * dy[curs] << " " << curx + (s - cur) * dx[curs], 0;
        }
        else if (curx < 1) {
            if (curs != 2) return cout << cury + (s - cur) * dy[curs] << " " << curx + (s - cur) * dx[curs], 0;
        }
        else if (cury < 1) {
            if (curs != 3) return cout << cury + (s - cur) * dy[curs] << " " << curx + (s - cur) * dx[curs], 0;
        }
        else if (curx > n) {
            if (curs != 0) return cout << cury + (s - cur) * dy[curs] << " " << curx + (s - cur) * dx[curs], 0;
        }
        //cout << cur << " " << curx << " " << cury << " " << curs << "\n";
        if (f) continue;

        if (!mm.count({curs, {curx, cury}})) mm[{curs, {curx, cury}}] = cur;
        else {
            int rem = s - cur;
            rem %= (cur - mm[{curs, {curx, cury}}]);
            f = true;
            cur = s - rem;
            //cout << cur << "\n";
        }
    }

    cout << cury << " " << curx;
    return 0;
}
/*
4 3 5 9
###.
#...
#..#
##.#

3 2 5 7
###
#..
#..

12 11 11 987654321
############
#..#...##.##
#..#.#.#.#.#
####.#.#####
#....#.....#
#.########.#
#...#......#
###.#.######
#...#......#
#.########.#
#..........#
############
*/
