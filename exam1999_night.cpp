#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

double d[N], x[N], y[N];
vector <pair <double, int> > g[N];
int n;

int main(){
    #ifndef Futymy
        freopen("nightin.txt", "r", stdin);
        freopen("nightout.txt", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> x[0] >> y[0] >> x[1] >> y[1];
    cin >> n; x[n + 1] = x[1]; y[n + 1] = y[1];
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            if (i == j) continue;
            double dist = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
            if (dist <= 2500) g[i].push_back({sqrt(dist), j}), g[j].push_back({sqrt(dist), i});
        }
    }

    for (int i = 0; i <= n + 1; i++) d[i] = 1e9;
    d[0] = 0;
    priority_queue <pair <double, int>, vector <pair <double, int> >, greater <pair <double, int> > > pq;
    pq.push({d[0], 0});
    while (!pq.empty()) {
        double dist = pq.top().first;
        int u = pq.top().second; pq.pop();
        if (dist != d[u]) continue;
        for (auto i: g[u]) {
            double w = i.first;
            int v = i.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }

    cout << fixed << setprecision(3) << d[n + 1];
    return 0;
}
