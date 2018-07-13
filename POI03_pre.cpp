#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int l, d;
        cin >> l >> d;

        double L = 0;
        double R = pi;

        while (abs(L - R) > 1e-15) {
            double mid = (L + R)/2;

            double res = mid * l / (2 * sin(mid / 2.00));

            if (res > l + d) R = mid;
            else L = mid;
        }

        int ans = round(-l / (2.00 * tan(L / 2.00)) + l / (2.00 * sin(L / 2.00)));

        cout << ans << "\n";
    }
    return 0;
}
