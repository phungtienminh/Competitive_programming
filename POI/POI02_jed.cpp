#include <bits/stdc++.h>

using namespace std;

const int N = 20005;
int n;

string bfs() {
    int dist[N];
    string ans[N];
    memset(dist, 0x3f, sizeof(dist));

    queue <int> q;
    dist[1] = 0;
    ans[1] = "1";
    q.push(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == 0) return ans[u];

        if (dist[(u * 10) % n] > dist[u] + 1) {
            dist[(u * 10) % n] = dist[u] + 1;
            ans[(u * 10) % n] = ans[u] + "0";
            q.push((u * 10) % n);
        }

        if (dist[(u * 10 + 1) % n] > dist[u] + 1) {
            dist[(u * 10 + 1) % n] = dist[u] + 1;
            ans[(u * 10 + 1) % n] = ans[u] + "1";
            q.push((u * 10 + 1) % n);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << bfs() << "\n";
    }
    return 0;
}
