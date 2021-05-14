#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, a[N], f[N];
map <int, vector <int> > mm;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), f[i] = 1;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) mm[a[i]].push_back(i);
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (mm[a[i] - a[j]].size() > 1 || (mm[a[i] - a[j]].size() == 1 && mm[a[i] - a[j]][0] != j)) f[i] = max(f[i], f[j] + 1);
        }
    }

    printf("%d", *max_element(f + 1, f + n + 1));
    return 0;
}
