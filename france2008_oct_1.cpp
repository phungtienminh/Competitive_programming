#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int cnt[N], x, y, n;

int main(){
    scanf("%d %d", &x, &y);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int val;
        scanf("%d", &val);
        cnt[val]++;
    }

    puts(cnt[x] > cnt[y] ? "Premier" : (cnt[x] < cnt[y] ? "Second" : "Ex-aequo"));
    return 0;
}
