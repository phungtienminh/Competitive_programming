#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

bool instack[N];

struct AhoCorasick {
    struct Node {
        int child[2], nxt[2], link, par;
        bool deadEnd;
        Node(){
            memset(child, 0, sizeof(child));
            memset(nxt, 0, sizeof(nxt));
            link = 0;
            par = 0;
            deadEnd = false;
        }
    } node[N];

    int cnt = 0;
    bool visited[N];
    queue <int> q;

    void add (string s) {
        int cur = 0;
        for (int i = 0; i < s.length(); i++) {
            int ch = s[i] - '0';
            if (!node[cur].child[ch]) {
                node[cur].child[ch] = ++cnt;
                node[cnt].par = cur;
            }

            cur = node[cur].child[ch];
        }

        node[cur].deadEnd = true;
    }

    void bfs(){
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int ch = 0; ch < 2; ch++) {
                int v = node[u].child[ch];
                node[u].nxt[ch] = node[node[u].link].nxt[ch];
                if (!v) node[u].child[ch] = node[node[u].link].child[ch];
                else {
                    node[v].link = node[u].nxt[ch];
                    node[u].nxt[ch] = v;
                    q.push(v);
                }
            }

            if (node[node[u].link].deadEnd) node[u].deadEnd = true;
        }
    }

    void dfs (int u) {
        visited[u] = true;
        instack[u] = true;
        //cout << u << '\n';
        for (int ch = 0; ch < 2; ch++) {
            int v = node[u].child[ch];
            /*(!v) {
                //cout << "TAK";
                //exit(0);
                continue;
            }*/
            if (!visited[v] && !node[v].deadEnd) dfs(v);
            else if (instack[v]) {
                cout << "TAK";
                exit(0);
            }
        }

        /*//if (u == 3) cout << "VIT " << node[u].link << " " << node[u].par << "\n";
        if (node[u].link != node[u].par && instack[node[u].link] && !node[node[u].link].deadEnd) {
            //cout << "VIT2 " << u << "\n";
            cout << "TAK";
            exit(0);
        }
        else if (node[u].link != node[u].par && !node[node[u].link].deadEnd) dfs(node[u].link);
        //node[u].deadEnd = true;*/
        instack[u] = false;
    }
} aho;

int n;
string s;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        aho.add(s);
    }

    aho.bfs();
    aho.dfs(0);
    cout << "NIE";
    return 0;
}
