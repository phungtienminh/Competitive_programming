#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, connect[N], cnt = 0;
map <long long, int> comp;
map <int, string> result[N];
map <int, bool> mm[N];
string a[N];

class Flows {
private:
    struct edge {
        int u, v, cap, flow;
        edge (int u = 0, int v = 0, int cap = 0, int flow = 0): u(u), v(v), cap(cap), flow(flow) {}
        int other (edge ed, int u) {
            return ed.u == u ? ed.v : ed.u;
        }
    } E;

    int S, T, dist[N], par[N], ptr[N];
    vector <edge> e;
    vector <int> g[N];
    bool inqueue[N];
    queue <int> q;

    void prep(){
        for (int i = 0; i <= 5 * n + 1; i++) {
            dist[i] = 1e9 + 2277;
            par[i] = -1;
            ptr[i] = 0;
            inqueue[i] = 0;
        }
    }

    bool spfa(){
        prep();
        q.push(S); dist[S] = 0; par[S] = 1e9 + 2277; inqueue[S] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop(); inqueue[u] = false;
            for (auto V: g[u]) {
                edge ed = e[V];
                int v = E.other(ed, u);
                if (dist[v] > dist[u] + 1 && ed.flow < ed.cap) {
                    dist[v] = dist[u] + 1;
                    par[v] = V;
                    if (!inqueue[v]) {
                        inqueue[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        return par[T] != -1;
    }

    int dinic (int u, int flow) {
        if (u == T || !flow) return flow;
        for (int &i = ptr[u]; i < g[u].size(); i++) {
            int V = g[u][i];
            edge ed = e[V];
            int v = E.other(ed, u);
            if (dist[v] == dist[u] + 1 && ed.flow < ed.cap) {
                int delta = dinic(v, min(flow, ed.cap - ed.flow));
                if (delta > 0) {
                    e[V].flow += delta;
                    e[V ^ 1].flow -= delta;
                    return delta;
                }
            }
        }

        return 0;
    }

public:
    void init (int _S, int _T) {
        S = _S;
        T = _T;
    }

    void addEdge (int u, int v, int cap, int flow) {
        if (mm[u].count(v)) return;
        mm[u][v] = 1;
        g[u].push_back(e.size());
        e.push_back(edge(u, v, cap, flow));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, 0));
    }

    int getFlow(){
        int ans = 0;
        while (spfa()) while (int cur = dinic(S, (int)1e9 + 2277)) ans += cur;
        for (auto i: e) if (i.flow > 0 && i.u >= 1 && i.u <= n && i.v >= n + 1 && i.v <= cnt) connect[i.u] = i.v;
        return ans;
    }
} mf;

long long query (long long x, long long y, char op) {
    if (op == '+') return x + y;
    if (op == '-') return x - y;
    return x * y;
}

string toStr (int x) {
    if (x == 0) return "0";
    string ans = "";
    while (x > 0) {
        ans = (char)(x % 10 + 48) + ans;
        x /= 10;
    }

    return ans;
}

void proc (string s, int id) {
    vector <int> vec;
    vector <char> oper;

    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') num = (num << 3) + (num << 1) + (s[i] - '0');
        else {
            vec.push_back(num);
            oper.push_back(s[i]);
            num = 0;
        }
    }

    vec.push_back(num);
    if (vec.size() == 2) {
        long long res = query(vec[0], vec[1], oper[0]);
        if (!comp.count(res)) comp[res] = ++cnt;
        result[comp[res]][id] = s;

        mf.addEdge(id, comp[res], 1, 0);
    }
    else if (vec.size() == 3) {
        //a?b?c
        if (oper[0] != '*' && oper[1] != '*') {
            long long res = query(vec[0], vec[1], oper[0]);
            res = query(res, vec[2], oper[1]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;
            mf.addEdge(id, comp[res], 1, 0);

            if (oper[0] == '-') {
                res = query(vec[1], vec[2], oper[1]);
                res = query(vec[0], res, oper[0]);
                if (!comp.count(res)) comp[res] = ++cnt;
                string t = "";
                t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]); t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);
            }
        }
        else if (oper[0] == '*' && oper[1] == '*') {
            long long res = 1LL * vec[0] * vec[1] * vec[2];
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
        }
        else if (oper[0] == '*' && oper[1] != '*') {
            //a*b?c
            long long res = 1LL * vec[0] * vec[1];
            res = query(res, vec[2], oper[1]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            res = query(vec[1], vec[2], oper[1]);
            res = query(res, vec[0], oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t = toStr(vec[0]); t += oper[0];
            //cout << "DEBUG " << vec[0] << " " << vec[1] << " " << vec[2] << "\n";
            t += '('; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]); t += ')';
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);
        }
        else {
            //a?b*c
            long long res = 1LL * vec[1] * vec[2];
            res = query(vec[0], res, oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            res = query(vec[0], vec[1], oper[0]);
            res = query(res, vec[2], oper[1]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t += '('; t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += ')';
            t += oper[1]; t = t + toStr(vec[2]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);
        }
    }
    else {
        if (oper[0] != '*' && oper[1] != '*' && oper[2] != '*') {
            long long res = query(vec[0], vec[1], oper[0]);
            res = query(res, vec[2], oper[1]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;
            mf.addEdge(id, comp[res], 1, 0);

            if (oper[0] == '-') {
                //a-(b-c-d)
                res = query(vec[1], vec[2], oper[1]); res = query(res, vec[3], oper[2]); res = query(vec[0], res, oper[0]);
                if (!comp.count(res)) comp[res] = ++cnt;
                string t = ""; t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1];
                t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);

                if (oper[1] == '-') { //a-(b-(c-d))
                    res = query(vec[2], vec[3], oper[2]); res = query(vec[1], res, oper[1]); res = query(vec[0], res, oper[0]);
                    if (!comp.count(res)) comp[res] = ++cnt; t = "";
                    t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1]; t += '(';
                    t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')'; t += ')';
                    result[comp[res]][id] = t;
                    mf.addEdge(id, comp[res], 1, 0);
                }
            }
            else {
                if (oper[1] == '-') { //a+b-(c-d)
                    res = query(vec[2], vec[3], oper[2]); res = query(vec[1], res, oper[1]); res = query(vec[0], res, oper[0]);
                    if (!comp.count(res)) comp[res] = ++cnt; string t = "";
                    t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1]; t += '(';
                    t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')';
                    result[comp[res]][id] = t;
                    mf.addEdge(id, comp[res], 1, 0);
                }
            }
        }
        else if (oper[0] == '*' && oper[1] == '*' && oper[2] == '*') {
            long long res = query(vec[0], vec[1], oper[0]);
            res = query(res, vec[2], oper[1]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
        }
        else if (oper[0] == '*' && oper[1] != '*' && oper[2] != '*') { //a*b+c+d
            //a*b+c+d
            long long res = query(vec[0], vec[1], oper[0]);
            res = query(res, vec[2], oper[1]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            //a*(b+c)+d
            res = query(vec[1], vec[2], oper[1]); res = query(res, vec[0], oper[0]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]);
            t += ')'; t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //a*(b+c+d)
            res = query(vec[1], vec[2], oper[1]); res = query(res, vec[3], oper[2]); res = query(res, vec[0], oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = "";
            t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]); t += ')';
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            if (oper[1] == '-') { //a*b-(c-d)
                res = query(vec[2], vec[3], oper[2]);
                long long temp = query(vec[0], vec[1], oper[0]);
                res = query(temp, res, oper[1]);
                if (!comp.count(res)) comp[res] = ++cnt;
                t = ""; t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1];
                t += '('; t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);

                //a*(b-(c-d))
                res = query(vec[2], vec[3], oper[2]); res = query(vec[1], res, oper[1]); res = query(vec[0], res, oper[0]);
                if (!comp.count(res)) comp[res] = ++cnt;
                t = ""; t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1]; t += '(';
                t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')'; t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);
            }
        }
        else if (oper[0] != '*' && oper[1] == '*' && oper[2] != '*') { //a+b*c+d
            //a+b*c+d
            long long res = query(vec[1], vec[2], oper[1]);
            res = query(vec[0], res, oper[0]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            //(a+b)*c+d
            res = query(vec[0], vec[1], oper[0]); res = query(res, vec[2], oper[1]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t += '('; t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += ')'; t += oper[1]; t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //a+b*(c+d)
            res = query(vec[2], vec[3], oper[2]); res = query(res, vec[1], oper[1]); res = query(vec[0], res, oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = "";
            t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1]; t += '('; t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]); t += ')';
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //(a+b)*(c+d)
            long long temp = query(vec[0], vec[1], oper[0]);
            res = query(vec[2], vec[3], oper[2]); res = query(res, temp, oper[1]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = "";
            t += '(';
            t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += ')'; t += oper[1];
            t += '('; t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]); t += ')';
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);
            if (oper[0] == '-') {
                //a-b*(c+d)
                res = query(vec[2], vec[3], oper[2]); res = query(vec[1], res, oper[1]); res = query(vec[0], res, oper[0]);
                if (!comp.count(res)) comp[res] = ++cnt;
                t = ""; t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1]; t += '(';
                t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);

                //a-(b*c+d)
                res = query(vec[1], vec[2], oper[1]); res = query(res, vec[3], oper[2]); res = query(vec[0], res, oper[0]);
                if (!comp.count(res)) comp[res] = ++cnt;
                t = ""; t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1];
                t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);
            }
        }
        else if (oper[0] != '*' && oper[1] != '*' && oper[2] == '*') {
            //a+b+c*d
            long long res = query(vec[2], vec[3], oper[2]);
            res = query(res, vec[0], oper[0]); res = query(res, vec[1], oper[1]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            //a+(b+c)*d
            res = query(vec[1], vec[2], oper[1]); res = query(res, vec[3], oper[2]); res = query(res, vec[0], oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t = t + toStr(vec[0]); t += oper[0]; t += '(';
            t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]); t += ')';
            t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //(a+b+c)*d
            res = query(vec[0], vec[1], oper[0]); res = query(res, vec[2], oper[1]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = ""; t += '(';
            t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]); t += ')';
            t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            if (oper[0] == '-') {
                //a-(b+c*d)
                res = query(vec[2], vec[3], oper[2]); res = query(vec[1], res, oper[1]); res = query(vec[0], res, oper[0]);
                if (!comp.count(res)) comp[res] = ++cnt;
                t = ""; t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1];
                t = t + toStr(vec[2]); t += oper[2]; t = t + toStr(vec[3]); t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);

                //a-((b+c)*d)
                res = query(vec[1], vec[2], oper[1]); res = query(res, vec[3], oper[2]); res = query(vec[0], res, oper[0]);
                if (!comp.count(res)) comp[res] = ++cnt;
                t = ""; t = t + toStr(vec[0]); t += oper[0]; t += '('; t += '('; t = t + toStr(vec[1]); t += oper[1];
                t = t + toStr(vec[2]); t += ')'; t += oper[2]; t = t + toStr(vec[3]); t += ')';
                result[comp[res]][id] = t;
                mf.addEdge(id, comp[res], 1, 0);
            }
        }
        else if (oper[0] == '*' && oper[1] == '*' && oper[2] != '*') {
            //a*b*c+d
            long long res = query(vec[1], vec[2], oper[1]);
            res = query(res, vec[0], oper[0]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            //a*b*(c+d)
            res = query(vec[2], vec[3], oper[2]); res = query(res, vec[1], oper[1]); res = query(res, vec[0], oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1]; t += '('; t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]); t += ')';
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //a*(b*c+d)
            res = query(vec[1], vec[2], oper[1]); res = query(res, vec[3], oper[2]); res = query(res, vec[0], oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = "";
            t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]); t += ')';
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);
        }
        else if (oper[0] == '*' && oper[1] != '*' && oper[2] == '*') {
            //a*b+c*d
            long long res = query(vec[0], vec[1], oper[0]); long long temp = query(vec[2], vec[3], oper[2]);
            res = query(res, temp, oper[1]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            //(a*b+c)*d
            res = query(vec[0], vec[1], oper[0]); res = query(res, vec[2], oper[1]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t += '('; t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]);
            t += ')';
            t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //a*(b+c)*d
            res = query(vec[1], vec[2], oper[1]); res = query(res, vec[3], oper[2]); res = query(res, vec[0], oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = "";
            t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]);
            t += ')'; t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //a*(b+c*d)
            temp = query(vec[2], vec[3], oper[2]);
            res = query(vec[1], temp, oper[1]); res = query(res, vec[0], oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = "";
            t = t + toStr(vec[0]); t += oper[0]; t += '('; t = t + toStr(vec[1]); t += oper[1];
            t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]); t += ')';
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);
        }
        else {
            //a+b*c*d
            long long res = query(vec[1], vec[2], oper[1]);
            res = query(res, vec[3], oper[2]); res = query(vec[0], res, oper[0]);
            if (!comp.count(res)) comp[res] = ++cnt;
            result[comp[res]][id] = s;

            mf.addEdge(id, comp[res], 1, 0);
            //(a+b)*c*d
            res = query(vec[0], vec[1], oper[0]); res = query(res, vec[2], oper[1]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            string t = "";
            t += '('; t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += ')'; t += oper[1]; t = t + toStr(vec[2]);
            t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);

            //(a+b*c)*d
            long long temp = query(vec[1], vec[2], oper[1]);
            res = query(vec[0], temp, oper[0]); res = query(res, vec[3], oper[2]);
            if (!comp.count(res)) comp[res] = ++cnt;
            t = ""; t += '(';
            t = t + toStr(vec[0]); t += oper[0]; t = t + toStr(vec[1]); t += oper[1]; t = t + toStr(vec[2]);
            t += ')';
            t += oper[2]; t = t + toStr(vec[3]);
            result[comp[res]][id] = t;

            mf.addEdge(id, comp[res], 1, 0);
        }
    }
}

int main(){
    //freopen("all.inp", "r", stdin);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n; cnt = n; mf.init(0, 5 * n + 1);
    for (int i = 1; i <= n; i++) mf.addEdge(0, i, 1, 0);
    for (int i = n + 1; i <= 5 * n; i++) mf.addEdge(i, 5 * n + 1, 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        proc(a[i], i);
    }

    int ans = mf.getFlow();
    if (ans < n) cout << "NO SOLUTION";
    else for (int i = 1; i <= n; i++) cout << result[connect[i]][i] << "\n";
    return 0;
}
/*
3
2*3-4
2*3-4
3*2-4
*/
