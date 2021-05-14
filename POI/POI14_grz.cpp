#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, a[N][N], ridge = 0, valley = 0;
bool visited[N][N], isRidge = 0, isValley = 0;
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool inside (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

void dfs (int x, int y, int height) {
    visited[x][y] = true;
    for (int i = 0; i < 8; i++) {
        if (inside(x + dx[i], y + dy[i])) {
            if (!visited[x + dx[i]][y + dy[i]] && a[x + dx[i]][y + dy[i]] == height) dfs(x + dx[i], y + dy[i], height);
            else if (a[x + dx[i]][y + dy[i]] < height) isRidge = true;
            else if (a[x + dx[i]][y + dy[i]] > height) isValley = true;
        }
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!visited[i][j]) {
                isRidge = 0; isValley = 0;
                dfs(i, j, a[i][j]);
                if (isRidge && isValley) continue;
                if (!isRidge && !isValley) ridge++, valley++;
                else if (isRidge) ridge++;
                else valley++;
            }
        }
    }

    cout << ridge << " " << valley;
    return 0;
}
