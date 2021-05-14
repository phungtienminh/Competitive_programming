#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int maxn = 305;

char ans[maxn][maxn];
int n, xt, yt, MaxX = -1e9, MaxY = -1e9, MinX = 1e9, MinY = 1e9;
pair <pair <int, int>, pair <int, int> > a[N];
vector <int> vec[maxn][maxn], g[N];
bool visited[N];

void dfs (int u) {
    visited[u] = true;
    for (auto v: g[u]) if (!visited[v]) dfs(v);
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < maxn; i++) for (int j = 0; j < maxn; j++) ans[i][j] = '.';
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d %d", &a[i].first.first, &a[i].first.second, &a[i].second.first, &a[i].second.second);
        vec[a[i].first.first][a[i].first.second].push_back(i);
        vec[a[i].second.first][a[i].second.second].push_back(i);
    }

    scanf("%d %d", &xt, &yt);
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 1; k < vec[i][j].size(); k++) {
                g[vec[i][j][k - 1]].push_back(vec[i][j][k]);
                g[vec[i][j][k]].push_back(vec[i][j][k - 1]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (a[i].first.first == a[i].second.first) {
            if (a[i].first.first == xt && min(a[i].first.second, a[i].second.second) <= yt && yt <= max(a[i].first.second, a[i].second.second)) dfs(i);
        }
        else {
            if (a[i].first.second == yt && min(a[i].first.first, a[i].second.first) <= xt && xt <= max(a[i].first.first, a[i].second.first)) dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            MaxX = max(MaxX, max(a[i].first.first, a[i].second.first));
            MinX = min(MinX, min(a[i].first.first, a[i].second.first));
            MaxY = max(MaxY, max(a[i].first.second, a[i].second.second));
            MinY = min(MinY, min(a[i].first.second, a[i].second.second));
        }
    }

    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            if (a[i].first.first == a[i].second.first) {
                for (int j = min(a[i].first.second, a[i].second.second); j <= max(a[i].first.second, a[i].second.second); j++) {
                    //ans[a[i].first.first - MinX + 1][MaxY - MinY + 1 - (j - MinY + 1) + 1] = '#';
                    ans[MaxY - MinY + 1 - (j - MinY + 1) + 1][a[i].first.first - MinX + 1] = '#';
                }
            }
            else {
                for (int j = min(a[i].first.first, a[i].second.first); j <= max(a[i].first.first, a[i].second.first); j++) {
                    //ans[j - MinX + 1][MaxY - MinY + 1 - (a[i].first.second - MinY + 1) + 1] = '#';
                    ans[MaxY - MinY + 1 - (a[i].first.second - MinY + 1) + 1][j - MinX + 1] = '#';
                }
            }
        }
    }

    for (int i = 1; i <= MaxY - MinY + 1; i++) {
        for (int j = 1; j <= MaxX - MinX + 1; j++) {
            printf("%c", ans[i][j]);
        }
        puts("");
    }
    return 0;
}
