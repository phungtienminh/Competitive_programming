#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const long long inf = 1e18;

int n, k, m, in[N];
vector <int> vec;
vector <pair <int, int> > g[N];

long long dist[5][N], dist2[5][5][N];

void dijkstra (int s, int ind) {
    priority_queue <pair <long long, int>, vector <pair <long long, int> >, greater <pair <long long, int> > > pq;
    for (int i = 1; i <= n; i++) dist[ind][i] = inf;
    dist[ind][s] = 0; pq.push({dist[ind][s], s});
    while (!pq.empty()) {
        pair <long long, int> val = pq.top(); pq.pop();
        long long d = val.first;
        int u = val.second;
        if (d == dist[ind][u]) {
            for (auto v: g[u]) {
                if (dist[ind][v.second] > dist[ind][u] + v.first) {
                    dist[ind][v.second] = dist[ind][u] + v.first;
                    pq.push({dist[ind][v.second], v.second});
                }
            }
        }
    }
}

void redijkstra (int s, int t) {
    priority_queue <pair <long long, int>, vector <pair <long long, int> >, greater <pair <long long, int> > > pq;
    for (int i = 1; i <= n; i++) {
        dist2[in[s]][in[t]][i] = dist[in[s]][i] + dist[in[t]][i];
        pq.push({dist2[in[s]][in[t]][i], i});
    }

    while (!pq.empty()) {
        pair <long long, int> val = pq.top(); pq.pop();
        long long d = val.first;
        int u = val.second;
        if (d == dist2[in[s]][in[t]][u]) {
            for (auto v: g[u]) {
                if (dist2[in[s]][in[t]][v.second] > dist2[in[s]][in[t]][u] + v.first) {
                    dist2[in[s]][in[t]][v.second] = dist2[in[s]][in[t]][u] + v.first;
                    pq.push({dist2[in[s]][in[t]][v.second], v.second});
                }
            }
        }
    }
}

int main(){
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 1; i <= k; i++) {
        int x;
        scanf("%d", &x);
        vec.push_back(x);
    }

    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    k = vec.size();
    for (int i = 0; i < vec.size(); i++) in[vec[i]] = i;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }

    for (int i = 0; i < vec.size(); i++) dijkstra(vec[i], i);

    if (k == 2) printf("%lld", dist[in[vec[0]]][vec[1]]);
    else if (k == 3) {
        long long ans = 1e18;
        for (int i = 1; i <= n; i++) ans = min(ans, dist[in[vec[0]]][i] + dist[in[vec[1]]][i] + dist[in[vec[2]]][i]);
        ans = min(ans, dist[in[vec[0]]][vec[1]] + dist[in[vec[1]]][vec[2]]);
        ans = min(ans, dist[in[vec[0]]][vec[1]] + dist[in[vec[0]]][vec[2]]);
        ans = min(ans, dist[in[vec[0]]][vec[2]] + dist[in[vec[1]]][vec[2]]);
        printf("%lld", ans);
    }
    else {
        long long ans = 1e18;
        for (int i = 0; i < vec.size(); i++) for (int j = 0; j < vec.size(); j++) redijkstra(vec[i], vec[j]);
        if (k == 4) {
            do {
                for (int i = 1; i <= n; i++) ans = min(ans, dist2[in[vec[0]]][in[vec[1]]][i] + dist2[in[vec[2]]][in[vec[3]]][i]);
            } while (next_permutation(vec.begin(), vec.end()));

            printf("%lld", ans);
        }
        else {
            do {
                for (int i = 1; i <= n; i++) ans = min(ans, dist2[in[vec[0]]][in[vec[1]]][i] + dist2[in[vec[2]]][in[vec[3]]][i] + dist[in[vec[4]]][i]);
            } while (next_permutation(vec.begin(), vec.end()));

            printf("%lld", ans);
        }
    }
    return 0;
}
/*
4 3 6
1 3 4
1 2 4
1 3 9
1 4 6
2 3 2
2 4 5
3 4 8
*/
