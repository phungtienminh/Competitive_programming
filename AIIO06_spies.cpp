#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

pair <int, int> a[N];
int n;

int main(){
    #ifndef Futymy
        freopen("spiesin.txt", "r", stdin);
        freopen("spiesout.txt", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1);
    printf("%d ", a[(n + 1) / 2].first);
    for (int i = 1; i <= n; i++) swap(a[i].first, a[i].second);
    sort(a + 1, a + n + 1);
    printf("%d", a[(n + 1) / 2].first);
    return 0;
}
