#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

vector <int> ans_num, ans_char;
int deg[N], n, child[N];
int cur = 1;
int cur_node = 1;
bool ok = true;

void dfs (int u, int d) {
    if (cur > n) return;
    if (cur_node >= N) {
        ok = false;
        return;
    }
    ans_char.push_back('(');

    if (d == deg[cur]) {
        ans_char.push_back(')');
        cur++;
        return;
    }

    if (child[u] < 2) {
        child[u]++;
        cur_node++;
        ans_num.push_back(u);
        dfs(cur_node, d + 1);
    }

    if (cur <= n && child[u] < 2) {
        child[u]++;
        cur_node++;
        ans_num.push_back(u);
        dfs(cur_node, d + 1);
    }

    ans_char.push_back(')');
}

int main(){
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) scanf("%d", &deg[i]);

    ans_num.push_back(0);
    memset(child, 0, sizeof(child));
    dfs(cur_node, 0);

    for (int i = 0; i < N; i++) if (child[i] == 1) ok = false;
    if (cur <= n || !ok) printf("NIE");
    else {
        for (int i = 0; i < ans_num.size(); i++) {
            if (i) putchar(' ');
            printf("%d", ans_num[i]);
        }

        puts("");
        for (int i = 0; i < ans_char.size(); i++) printf("%c", ans_char[i]);
        puts("");
    }
    return 0;
}
