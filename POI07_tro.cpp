#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 5;

struct data {
    int i, j, k;

    data (int i = 0, int j = 0, int k = 0): i(i), j(j), k(k) {}
};

bool used[N];
vector <data> ans;
int n, p, q;

int main(){
    scanf("%d %d %d", &p, &q, &n);
    if (p > q) swap(p, q);
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            if (!used[i + p]) {
                ans.push_back(data(i, i + p, i + p + q));
                used[i] = used[i + p] = used[i + p + q] = true;
            }
            else {
                ans.push_back(data(i, i + q, i + p + q));
                used[i] = used[i + q] = used[i + p + q] = true;
            }
        }
    }

    printf("%d\n", (int)ans.size());
    for (auto i: ans) printf("%d %d %d\n", i.i, i.j, i.k);
    return 0;
}
