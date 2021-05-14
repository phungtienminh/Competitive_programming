#include <bits/stdc++.h>

using namespace std;

const int N = 30005;
int a[N];

int main(){
    int w, n;
    scanf("%d %d", &w, &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);

    int ans = 0;
    int l = 1;
    int r = n;

    while (l < r) {
        if (a[l] + a[r] > w) {
            r--;
            ans++;
        }
        else {
            l++;
            r--;
            ans++;
        }
    }

    if (l == r) ans++;
    printf("%d", ans);
    return 0;
}
