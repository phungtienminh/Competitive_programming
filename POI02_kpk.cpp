#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int LEFT = 0;
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;

int dist[N][N][4], n, m, xs, ys, xf, yf;
char a[N][N];

struct Node {
    int row, col, direction;
} par[N][N][4];

class Data {
public:
    int row, col, direction;

    Data (int row, int col, int direction) {
        this->row = row;
        this->col = col;
        this->direction = direction;
    }
};

void bfs() {
    memset(dist, 0x3f, sizeof(dist));
    dist[xs][ys][0] = dist[xs][ys][1] = dist[xs][ys][2] = dist[xs][ys][3] = 0;
    queue <Data> q;
    for (int i = 0; i < 4; i++) q.push(Data(xs, ys, i));

    while (!q.empty()) {
        Data u = q.front(); q.pop();
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i * j != 0) continue;
                if (i == 0 && j == 0) continue;
                if (u.row + i < 1 || u.row + i > n || u.col + j < 1 || u.col + j > m) continue;
                if (a[u.row + i][u.col + j] == '1') continue;

                if (u.direction == LEFT && i == -1 && j == 0) {
                    if (dist[u.row + i][u.col + j][UP] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][UP] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, UP));
                        par[u.row + i][u.col + j][UP] = {u.row, u.col, LEFT};
                    }
                }

                if (u.direction == LEFT && i == 0 && j == -1) {
                    if (dist[u.row + i][u.col + j][LEFT] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][LEFT] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, LEFT));
                        par[u.row + i][u.col + j][LEFT] = {u.row, u.col, LEFT};
                    }
                }

                if (u.direction == UP && i == 0 && j == 1) {
                    if (dist[u.row + i][u.col + j][RIGHT] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][RIGHT] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, RIGHT));
                        par[u.row + i][u.col + j][RIGHT] = {u.row, u.col, UP};
                    }
                }

                if (u.direction == UP && i == -1 && j == 0) {
                    if (dist[u.row + i][u.col + j][UP] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][UP] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, UP));
                        par[u.row + i][u.col + j][UP] = {u.row, u.col, UP};
                    }
                }

                if (u.direction == RIGHT && i == 1 && j == 0) {
                    if (dist[u.row + i][u.col + j][DOWN] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][DOWN] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, DOWN));
                        par[u.row + i][u.col + j][DOWN] = {u.row, u.col, RIGHT};
                    }
                }

                if (u.direction == RIGHT && i == 0 && j == 1) {
                    if (dist[u.row + i][u.col + j][RIGHT] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][RIGHT] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, RIGHT));
                        par[u.row + i][u.col + j][RIGHT] = {u.row, u.col, RIGHT};
                    }
                }

                if (u.direction == DOWN && i == 0 && j == -1) {
                    if (dist[u.row + i][u.col + j][LEFT] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][LEFT] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, LEFT));
                        par[u.row + i][u.col + j][LEFT] = {u.row, u.col, DOWN};
                    }
                }

                if (u.direction == DOWN && i == 1 && j == 0) {
                    if (dist[u.row + i][u.col + j][DOWN] > dist[u.row][u.col][u.direction] + 1) {
                        dist[u.row + i][u.col + j][DOWN] = dist[u.row][u.col][u.direction] + 1;
                        q.push(Data(u.row + i, u.col + j, DOWN));
                        par[u.row + i][u.col + j][DOWN] = {u.row, u.col, DOWN};
                    }
                }
            }
        }
    }

    int ans = 0x3f3f3f3f;
    int pos = 0;
    for (int i = 0; i < 4; i++) {
        if (dist[xf][yf][i] < ans) {
            ans = dist[xf][yf][i];
            pos = i;
        }
    }

    if (ans == 0x3f3f3f3f) puts("NIE");
    else {
        printf("%d\n", ++ans);
        vector <pair <int, int> > res;
        int cur_x = xf;
        int cur_y = yf;

        while (dist[cur_x][cur_y][pos] > 0) {
            res.push_back(make_pair(cur_x, cur_y));
            int temp_x = cur_x;
            int temp_y = cur_y;

            cur_x = par[temp_x][temp_y][pos].row;
            cur_y = par[temp_x][temp_y][pos].col;
            pos = par[temp_x][temp_y][pos].direction;
        }

        res.push_back(make_pair(cur_x, cur_y));

        for (int i = (int)res.size() - 1; i >= 0; i--) printf("%d %d\n", res[i].first, res[i].second);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    getchar();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = getchar();
        }
        getchar();
    }
    scanf("%d %d", &xs, &ys);
    scanf("%d %d", &xf, &yf);

    bfs();
    return 0;
}
