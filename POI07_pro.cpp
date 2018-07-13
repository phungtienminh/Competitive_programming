#include <bits/stdc++.h>

using namespace std;

int main(){
    multiset <int> st;

    int n;
    scanf("%d", &n);

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            int x;
            scanf("%d", &x);
            st.insert(x);
        }

        int val_max = *st.rbegin();
        int val_min = *st.begin();
        st.erase(st.begin());
        st.erase(st.find(val_max));

        ans = ans + val_max - val_min;
    }

    printf("%lld", ans);
    return 0;
}
