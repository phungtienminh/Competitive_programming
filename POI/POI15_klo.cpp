#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k, a[N];
multiset <int> lpart, rpart;

void input(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
}

void solve(){
    if (k == 1) {
        printf("0\n");
        for (int i = 1; i <= n; i++) printf("%d\n", a[i]);
        return;
    }

    long long suml = 0;
    long long sumr = 0;
    long long Min = 1e18 + 2277;
    int pos = 0;
    int med = 0;

    for (int i = 1; i <= k; i++) {
        if (i <= (k + 1) / 2) {
            lpart.insert(a[i]);
            suml += a[i];
        }
        else {
            rpart.insert(a[i]);
            sumr += a[i];
        }
    }

    for (int i = 1; i <= n - k + 1; i++) {
        if (i > 1) {
            if (lpart.find(a[i - 1]) != lpart.end()) {
                lpart.erase(lpart.lower_bound(a[i - 1]));
                suml -= a[i - 1];
            }
            else {
                rpart.erase(rpart.lower_bound(a[i - 1]));
                sumr -= a[i - 1];
            }

            if (lpart.size() <= rpart.size()) {
                lpart.insert(a[i + k - 1]);
                suml += a[i + k - 1];
            }
            else {
                rpart.insert(a[i + k - 1]);
                sumr += a[i + k - 1];
            }
        }

        while (!lpart.empty() && !rpart.empty() && *rpart.begin() < *lpart.rbegin()) {
            int val_right = *rpart.begin();
            int val_left = *lpart.rbegin();
            multiset <int>::iterator it = lpart.end();

            suml = suml - val_left + val_right;
            sumr = sumr + val_left - val_right;

            rpart.erase(rpart.begin());
            rpart.insert(val_left);
            lpart.erase(--it);
            lpart.insert(val_right);
        }

        int mid = *lpart.rbegin();
        long long cur = 1LL * mid * (int)lpart.size() - suml + sumr - 1LL * mid * (int)rpart.size();

        if (cur < Min) {
            Min = cur;
            pos = i;
            med = mid;
        }
    }

    printf("%lld\n", Min);
    for (int i = pos; i <= pos + k - 1; i++) a[i] = med;
    for (int i = 1; i <= n; i++) printf("%d\n", a[i]);
}

int main(){
    input();
    solve();
    return 0;
}

/*
10 5
5 9 7 0 0 5 2 8 4 8
*/
