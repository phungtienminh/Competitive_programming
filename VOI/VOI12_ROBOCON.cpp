#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, k, dist[N][N], bl[N][N], dx[6] = {0, 1, 1, 0, 1, 1}, dy[6] = {1, 1, 0, -1, -1, 0}, ans = 0, state1[N][N], state2[N][N];
bool ban[N][N];

bool ok (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n && !ban[x][y];
}

vector <pair <int, int> > next_vec (vector <pair <int, int> > vec, int type) {
    vector <pair <int, int> > res;
    if (type == 1) {
        for (auto i: vec) {
            for (int j = 0; j < 3; j++) {
                if (ok(i.first + dx[j], i.second + dy[j]) && state1[i.first + dx[j]][i.second + dy[j]] != ans) {
                    state1[i.first + dx[j]][i.second + dy[j]] = ans;
                    res.push_back({i.first + dx[j], i.second + dy[j]});
                }
            }
        }
    }
    else {
        for (auto i: vec) {
            for (int j = 3; j < 6; j++) {
                if (ok(i.first + dx[j], i.second + dy[j]) && state2[i.first + dx[j]][i.second + dy[j]] != ans) {
                    state2[i.first + dx[j]][i.second + dy[j]] = ans;
                    res.push_back({i.first + dx[j], i.second + dy[j]});
                }
            }
        }
    }

    return res;
}

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        ban[x][y] = true;
    }

    vector <pair <int, int> > vec1, vec2;
    vec1.push_back({1, 1}); vec2.push_back({1, n});
    while (1) {
        ans++;
        vec1 = next_vec(vec1, 1);
        vec2 = next_vec(vec2, 2);
        for (auto i: vec1) if (state2[i.first][i.second] == ans) return !printf("%d", ans);
    }
    return 0;
}
