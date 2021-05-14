#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;
int a[N], dist[N], n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > pq;
    pq.push(make_pair(0, 0));

    while (!pq.empty()) {
        pair <int, int> topval = pq.top(); pq.pop();
        int d = topval.first;
        int u = topval.second;

        if (d == dist[u]) {
            for (int i = 1; i <= n; i++) {
                int v = (u + a[i]) % a[1];
                if (dist[v] > dist[u] + a[i]) {
                    dist[v] = dist[u] + a[i];
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int x;
        cin >> x;

        if (dist[x % a[1]] <= x) cout << "TAK\n";
        else cout << "NIE\n";
    }
    return 0;
}
