#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, a[N], rmq[N][20][2], ans = 0;

int get_min (int u, int v) {
    int k = log2(v - u + 1);
    return min(rmq[u][k][0], rmq[v - (1 << k) + 1][k][0]);
}

int get_max (int u, int v) {
    int k = log2(v - u + 1);
    return max(rmq[u][k][1], rmq[v - (1 << k) + 1][k][1]);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), rmq[i][0][0] = rmq[i][0][1] = a[i];
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            rmq[i][k][0] = min(rmq[i][k - 1][0], rmq[i + (1 << (k - 1))][k - 1][0]);
            rmq[i][k][1] = max(rmq[i][k - 1][1], rmq[i + (1 << (k - 1))][k - 1][1]);
        }
    }

    int ptr = 1; //start of a segment
    while (ptr <= n) {
        int l = ptr, r = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (get_min(ptr, mid) < a[ptr]) r = mid - 1;
            else l = mid + 1;
        }

        int max_far = r;
        int max_value = get_max(ptr, max_far);
        l = ptr; r = max_far;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (get_max(mid, max_far) != max_value) r = mid - 1;
            else l = mid + 1;
        }

        ans++; ptr = r + 1;
    }

    printf("%d", ans);
    return 0;
}
