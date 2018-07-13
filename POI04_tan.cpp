#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
int a[N], b[N];
pair <int, int> f[N], g[N];
int trace_f[N], trace_g[N];

int main(){
    int d, n;
    scanf("%d %d", &d, &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i], &b[i]);
    a[0] = b[0] = b[n + 1] = 0;
    a[n + 1] = d;

    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    f[0] = make_pair(0, 0);

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] >= a[i] - 800) {
                if (f[i].first > f[j].first + b[i]) {
                    f[i].first = f[j].first + b[i];
                    f[i].second = f[j].second + 1;
                    trace_f[i] = j;
                }
                else if (f[i].first == f[j].first + b[i] && f[i].second > f[j].second + 1) {
                    f[i].second = f[j].second + 1;
                    trace_f[i] = j;
                }
            }
        }
    }

    g[0] = make_pair(0, 0);
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] >= a[i] - 800) {
                if (g[i].first > g[j].first + 1) {
                    g[i].first = g[j].first + 1;
                    g[i].second = g[j].second + b[i];
                    trace_g[i] = j;
                }
                else if (g[i].first == g[j].first + 1 && g[i].second > g[j].second + b[i]) {
                    g[i].second = g[j].second + b[i];
                    trace_g[i] = j;
                }
            }
        }
    }

    vector <int> ans, res;
    int pos = n + 1;

    while (trace_f[pos]) {
        ans.push_back(trace_f[pos]);
        pos = trace_f[pos];
    }

    pos = n + 1;
    while (trace_g[pos]) {
        res.push_back(trace_g[pos]);
        pos = trace_g[pos];
    }

    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        if (i != (int)ans.size() - 1) printf(" ");
        printf("%d", a[ans[i]]);
    }

    puts("");
    for (int i = (int)res.size() - 1; i >= 0; i--) {
        if (i != (int)res.size() - 1) printf(" ");
        printf("%d", a[res[i]]);
    }

    puts("");
    return 0;
}
