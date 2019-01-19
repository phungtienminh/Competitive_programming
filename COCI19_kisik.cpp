#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

multiset <int> widths;
int n, k;

struct Item {
    int w, h;
    bool operator < (const Item &rhs) const {
        if (h != rhs.h) return h < rhs.h;
        return w < rhs.w;
    }
} a[N];

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].w, &a[i].h);
    sort(a + 1, a + n + 1);
    long long ans = 9e18;

    int ptr = 1;
    long long sum = 0;
    for (int i = 1; i <= n; i = ptr) {
        while (ptr <= n && a[ptr].h == a[i].h) widths.insert(a[ptr].w), sum += a[ptr].w, ptr++;
        if (widths.size() >= k) {
            while (widths.size() > k) {
                int val = *widths.rbegin();
                sum -= val;
                widths.erase(widths.find(val));
            }

            ans = min(ans, 1LL * sum * a[i].h);
        }
    }

    printf("%lld", ans);
    return 0;
}
