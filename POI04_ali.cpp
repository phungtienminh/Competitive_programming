#include <bits/stdc++.h>

using namespace std;

const int N = 50;
int dp[N][N][N];

class Data {
public:
    int x, y, z;
    Data (int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Node {
    int x1, y1, z1, x2, y2, z2;
} a[N];

int n;
int bfs (int xs, int ys, int zs, int xf, int yf, int zf) {
    memset(dp, 0x3f, sizeof(dp));
    dp[xs][ys][zs] = 0;

    queue <Data> q;
    q.push(Data(xs, ys, zs));

    while (!q.empty()) {
        Data u = q.front(); q.pop();
        if (u.x == xf && u.y == yf && u.z == zf) return dp[xf][yf][zf];
        for (int i = 1; i <= n; i++) {
            if (u.x - a[i].x1 + a[i].x2 < N && u.x >= a[i].x1 && u.y >= a[i].y1 && u.z >= a[i].z1 && u.y - a[i].y1 + a[i].y2 < N && u.z - a[i].z1 + a[i].z2 < N
                && dp[u.x - a[i].x1 + a[i].x2][u.y - a[i].y1 + a[i].y2][u.z - a[i].z1 + a[i].z2] > dp[u.x][u.y][u.z] + 1) {

                    dp[u.x - a[i].x1 + a[i].x2][u.y - a[i].y1 + a[i].y2][u.z - a[i].z1 + a[i].z2] = dp[u.x][u.y][u.z] + 1;
                    q.push(Data(u.x - a[i].x1 + a[i].x2, u.y - a[i].y1 + a[i].y2, u.z - a[i].z1 + a[i].z2));
            }
        }
    }

    return -1;
}

int main(){
    int t;
    scanf("%d", &t);

    while (t--) {
        int xs, ys, zs, xf, yf, zf;
        scanf("%d %d %d", &xs, &ys, &zs);
        scanf("%d %d %d", &xf, &yf, &zf);

        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d %d %d %d", &a[i].x1, &a[i].y1, &a[i].z1, &a[i].x2, &a[i].y2, &a[i].z2);
        }

        int ans = bfs(xs, ys, zs, xf, yf, zf);
        if (ans == -1) puts("NIE");
        else printf("%d\n", ans);
    }
    return 0;
}
