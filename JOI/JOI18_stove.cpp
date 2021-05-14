#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k, a[N], ans = 0;

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    ans = a[n] + 1 - a[1];
    priority_queue <int> pq;

    for (int i = 2; i <= n; i++) pq.push(a[i] - (a[i - 1] + 1));
    while (k > 1) {
        k--;
        ans -= pq.top();
        pq.pop();
    }

    printf("%d", ans);
    return 0;
}
