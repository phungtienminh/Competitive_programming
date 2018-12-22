#include <bits/stdc++.h>

using namespace std;

const int N = 65;

vector <vector <pair <int, int> > > pent;
vector <pair <int, int> > vec;
int n, m;
char a[N][N], b[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};
bool visited[N][N], used[6];

bool in (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void prep(){
    for (int x = 0; x <= 0; x++) {
        for (int y = 0; y <= 0; y++) {
            for (int x2 = -4; x2 <= 4; x2++) {
                for (int y2 = -4; y2 <= 4; y2++) {
                    if ((x == x2 && y == y2)) continue;
                    if (abs(x - x2) + abs(y - y2) > 1) continue;
                    for (int x3 = -4; x3 <= 4; x3++) {
                        for (int y3 = -4; y3 <= 4; y3++) {
                            if ((x3 == x && y3 == y) || (x3 == x2 && y3 == y2)) continue;
                            if (abs(x - x3) + abs(y - y3) > 1 && abs(x2 - x3) + abs(y2 - y3) > 1) continue;
                            for (int x4 = -4; x4 <= 4; x4++) {
                                for (int y4 = -4; y4 <= 4; y4++) {
                                    if ((x4 == x && y4 == y) || (x4 == x2 && y4 == y2) || (x4 == x3 && y4 == y3)) continue;
                                    if (abs(x - x4) + abs(y - y4) > 1 && abs(x2 - x4) + abs(y2 - y4) > 1 && abs(x3 - x4) + abs(y3 - y4) > 1) continue;
                                    for (int x5 = -4; x5 <= 4; x5++) {
                                        for (int y5 = -4; y5 <= 4; y5++) {
                                            if ((x5 == x && y5 == y) || (x5 == x2 && y5 == y2) || (x5 == x3 && y5 == y3) || (x5 == x4 && y5 == y4)) continue;
                                            if (abs(x - x5) + abs(y - y5) > 1 && abs(x2 - x5) + abs(y2 - y5) > 1 && abs(x3 - x5) + abs(y3 - y5) > 1 && abs(x4 - x5) + abs(y4 - y5) > 1) continue;
                                            pent.push_back({{x, y}, {x2, y2}, {x3, y3}, {x4, y4}, {x5, y5}});
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void bt (int x, int y, int covered, int character) {
    if (visited[x][y]) {
        if (y < m) bt(x, y + 1, covered, character);
        else bt(x + 1, 1, covered, character);
        return;
    }

    if (covered == n * m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << b[i][j];
            }

            cout << "\n";
        }

        exit(0);
    }

    for (int i = 0; i < pent.size(); i++) {
        vector <pair <int, int> > cur = pent[i];
        bool f = true;
        memset(used, 0, sizeof(used));
        for (auto j: cur) {
            if (!in(x + j.first, y + j.second)) {
                f = false;
                break;
            }

            if (visited[x + j.first][y + j.second]) {
                f = false;
                break;
            }

            if (used[a[x + j.first][y + j.second] - '0']) {
                f = false;
                break;
            }

            used[a[x + j.first][y + j.second] - '0'] = true;
        }

        if (!f) continue;
        for (auto j: cur) {
            visited[x + j.first][y + j.second] = true;
            b[x + j.first][y + j.second] = (char)(character + 65);
        }

        if (y < m) bt(x, y + 1, covered + 5, character + 1);
        else bt(x + 1, 1, covered + 5, character + 1);

        for (auto j: cur) {
            visited[x + j.first][y + j.second] = false;
            b[x + j.first][y + j.second] = '.';
        }
    }
}

int main(){
    #ifndef Futymy
        freopen("pentin.txt", "r", stdin);
        freopen("pentout.txt", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    prep(); reverse(pent.begin(), pent.end());
    bt(1, 1, 0, 0);
    return 0;
}
/*
5 5
12134
23455
43515
22432
51341
*/
