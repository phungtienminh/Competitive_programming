#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, nxt[20][N], q;
pair <int, int> queries[N];
vector <int> vec[N];

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> q; memset(nxt, -1, sizeof(nxt));
    for (int i = 1; i <= q; i++) {
        int x, y = -1;
        char c;
        cin >> c;
        if (c == 'E') cin >> x >> y;
        else cin >> x;

        if (c == 'E') vec[x].push_back(i);
        queries[i] = {x, y};
    }

    for (int i = 1; i <= q; i++) {
        if (queries[i].second == -1) continue;
        int y = queries[i].second;
        int pos = lower_bound(vec[y].begin(), vec[y].end(), i) - vec[y].begin();
        if (pos == vec[y].size()) nxt[0][i] = -1;
        else nxt[0][i] = vec[y][pos];
    }

    for (int i = 1; i < 20; i++) for (int j = 1; j <= q; j++) if (nxt[i - 1][j] != -1) nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
    for (int i = 1; i <= q; i++) {
        if (queries[i].second != -1) continue;
        int x = queries[i].first;
        if (!vec[x].size() || vec[x][0] > i) {
            printf("%d\n", x);
            continue;
        }

        int cur = vec[x][0];
        for (int j = 19; j >= 0; j--) {
            if (nxt[j][cur] > i || nxt[j][cur] == -1) continue;
            cur = nxt[j][cur];
        }

        printf("%d\n", queries[cur].second);
    }
    return 0;
}
