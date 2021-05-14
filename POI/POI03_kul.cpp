#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int maxn = 8005;
const int inf = 1e9 + 2277;

int cap[maxn], cost[maxn], f[maxn], par[N], dist[N], par_ind[N], n, s, t, flow;
int ans_cost = 0;
bool inqueue[N];
vector <pair <int, int> > g[N];

bool bfs() {
    if (!flow) return false;
    queue <int> q;
    for (int i = 1; i <= t; ++i) {
        par[i] = par_ind[i] = 0;
        dist[i] = inf;
        inqueue[i] = false;
    }

    q.push(s);
    dist[s] = 0;
    par[s] = par_ind[s] = -1;
    inqueue[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inqueue[u] = false;

        for (int i = 0; i < g[u].size(); ++i) {
            pair <int, int> v = g[u][i];
            if (f[v.second] < cap[v.second] && dist[v.first] > dist[u] + cost[v.second]) {
                dist[v.first] = dist[u] + cost[v.second];
                par[v.first] = u;
                par_ind[v.first] = v.second;
                if (!inqueue[v.first]) {
                    q.push(v.first);
                    inqueue[v.first] = true;
                }
            }
        }
    }

    return par[t] != 0;
}

void edmond_karp() {
    int u = t;
    int cur_flow = inf;

    while (u != s) {
        cur_flow = min(cur_flow, cap[par_ind[u]] - f[par_ind[u]]);
        u = par[u];
    }

    cur_flow = min(cur_flow, flow);
    flow -= cur_flow;
    ans_cost += cur_flow * dist[t];

    u = t;
    while (u != s) {
        f[par_ind[u]] += cur_flow;
        f[par_ind[u] ^ 1] -= cur_flow;
        u = par[u];
    }
}

int main(){
    cin >> n; s = n + 1; t = n + 2;
    int edge = 0;
    flow = 0;
    int cur;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        flow += x;

        g[s].push_back(make_pair(i, edge));
        cap[edge] += x;
        cost[edge] += 1;
        edge++;

        g[i].push_back(make_pair(s, edge));
        cost[edge] -= 1;
        edge++;
    }

    cur = flow;
    for (int i = 1; i <= n; ++i) {
        int j = (i + 1 > n ? 1 : i + 1);
        g[i].push_back(make_pair(j, edge));
        cap[edge] += inf;
        cost[edge] += 1;
        ++edge;

        g[j].push_back(make_pair(i, edge));
        cost[edge] -= 1;
        ++edge;

        g[j].push_back(make_pair(i, edge));
        cap[edge] += inf;
        cost[edge] += 1;
        ++edge;

        g[i].push_back(make_pair(j, edge));
        cost[edge] -= 1;
        ++edge;
    }

    for (int i = 1; i <= n; ++i) {
        g[i].push_back(make_pair(t, edge));
        cap[edge] += 1;
        cost[edge] += 1;
        ++edge;

        g[t].push_back(make_pair(i, edge));
        cost[edge] -= 1;
        ++edge;
    }

    while (bfs()) edmond_karp();

    cout << ans_cost - 2 * cur;
    return 0;
}
