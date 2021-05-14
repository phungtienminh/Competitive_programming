#include <bits/stdc++.h>

#define int long long

using namespace std;

const int K = 30;
const int N = 1e4 + 5;

int n, k, a[K];
multiset <int> st;

void input(){
    scanf("%lld %lld", &n, &k);
    for (int i = 1; i <= k; i++) scanf("%lld", &a[i]);
    sort(a + 1, a + k + 1);
}

void solve() {
    int sum = 0;
    for (int i = 1; i <= min(k, n); i++) {
        st.insert(a[i]);
        sum += a[i];
    }

    //Step 1: Add
    while (st.size() < n) {
        int val = *st.begin();
        sum = sum - val;
        st.erase(st.begin());

        for (int i = 1; i <= k; i++) {
            st.insert(val + a[i]);
            sum = sum + val + a[i];
            if (st.size() > n) {
                int nxt = *st.rbegin();
                sum -= nxt;
                st.erase(st.lower_bound(nxt));
            }
        }
    }

    //Step 2: Relax
    bool canDo = true;
    int now;
    while (canDo) {
        canDo = false;
        int val = *st.begin();
        st.erase(st.begin());
        now = sum;
        sum -= val;

        for (int i = 1; i <= k; i++) {
            st.insert(val + a[i]);
            sum = sum + val + a[i];
            if (st.size() > n) {
                int nxt = *st.rbegin();
                sum -= nxt;
                st.erase(st.lower_bound(nxt));
            }
        }

        if (sum < now) canDo = true;
    }

    printf("%lld", now);
}

signed main(){
    input();
    solve();
    return 0;
}
