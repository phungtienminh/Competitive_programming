#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, m, ans = 0;
bool visited[N][N];
string a[N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

bool ok (int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && a[x][y] != '*');
}

void bfs (queue <pair <int, int> > &q1, queue <pair <int, int> > &q2) {
    if (q1.empty()) return;
    ans++;
    while (!q1.empty()) {
        int x = q1.front().first, y = q1.front().second; q1.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!ok(nx, ny)) continue;
            visited[nx][ny] = true;
            if (a[nx][ny] == a[x][y]) q1.push({nx, ny});
            else q2.push({nx, ny});
        }
    }

    bfs(q2, q1);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    queue <pair <int, int> > q1, q2;
    q1.push({0, 0});
    visited[0][0] = true;
    bfs(q1, q2);
    cout << ans;
    return 0;
}
