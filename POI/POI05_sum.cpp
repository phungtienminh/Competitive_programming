#include <bits/stdc++.h>

#define int long long

using namespace std;

int get (int i) {
    //return sum of number from 1 to i.
    return (i + 1) * i / 2;
}

signed main(){
    int n, s;
    scanf("%lld %lld", &n, &s);
    vector <int> ans;
    ans.push_back(0);
    int sum = 0;

    if (s > 0) {
        for (int i = 1; i < n; i++) {
            int x = ans[i - 1] - 1;
            if (sum + x * (n - i) + get(n - i - 1) >= s) {
                sum += x;
                ans.push_back(x);
            }
            else {
                x = ans[i - 1] + 1;
                sum += x;
                ans.push_back(x);
            }
        }
    }
    else {
        for (int i = 1; i < n; i++) {
            int x = ans[i - 1] + 1;
            if (sum + x * (n - i) - get(n - i - 1) <= s) {
                sum += x;
                ans.push_back(x);
            }
            else {
                x = ans[i - 1] - 1;
                sum += x;
                ans.push_back(x);
            }
        }
    }

    if (sum != s) puts("NIE");
    else {
        for (int i = 0; i < ans.size(); i++) printf("%d\n", ans[i]);
    }
    return 0;
}
