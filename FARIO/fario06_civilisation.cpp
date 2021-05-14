#include <bits/stdc++.h>

using namespace std;

int main(){
    int w, h;
    scanf("%d %d", &w, &h);
    int a[h + 1][w + 1];
    for (int i = 1; i<=h; i++) {
        for (int j = 1; j<=w; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int dist[h + 1][w + 1];
    memset(dist, 0x3f, sizeof(dist));
    queue <pair <int, int> > q;
    for (int i = 1; i<=h; i++) {
        for (int j = 1; j<=w; j++) {
            if (a[i][j]) {
                dist[i][j] = 0;
                q.push(make_pair(i, j));
            }
        }
    }

    while (!q.empty()) {
        pair <int, int> onTop = q.front(); q.pop();
        for (int i = -1; i<=1; i++) {
            for (int j = -1; j<=1; j++) {
                if (i * j != 0) continue;
                if (onTop.first + i < 1 || onTop.first + i > h || onTop.second + j < 1 || onTop.second + j > w) continue;
                //if (a[onTop.first + i][onTop.second + j] == 1) continue;

                if (dist[onTop.first + i][onTop.second + j] > dist[onTop.first][onTop.second] + 1) {
                    dist[onTop.first + i][onTop.second + j] = dist[onTop.first][onTop.second] + 1;
                    q.push(make_pair(onTop.first + i, onTop.second + j));
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i<=h; i++) {
        for (int j = 1; j<=w; j++) {
            ans = max(ans, dist[i][j]);
           //cout << dist[i][j] << " ";
        }
        //cout << "\n";
    }
    printf("%d", ans);
    return 0;
}
