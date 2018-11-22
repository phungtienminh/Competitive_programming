#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int c, n, z, q, dp[N];

int main(){
    scanf("%d %d %d", &c, &n, &z);
    scanf("%d", &q);

    for (int i = 1; i <= 1000; i++) {
        vector <int> vec;
        for (int j = 0; j < i; j++) {
            if (j + c <= i) vec.push_back(dp[j] ^ dp[i - j - c]);
            if (j + n <= i) vec.push_back(dp[j] ^ dp[i - j - n]);
            if (j + z <= i) vec.push_back(dp[j] ^ dp[i - j - z]);
        }

        //for (auto j: vec) cout << j << " ";
        //cout << "\n";

        if (vec.size() == 0) {
            dp[i] = 0;
            continue;
        }

        sort(vec.begin(), vec.end()); vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
        if (vec[0] > 0) dp[i] = 0;
        else {
            bool f = false;
            for (int j = 1; j < vec.size(); j++) {
                if (vec[j] - vec[j - 1] > 1) {
                    dp[i] = vec[j - 1] + 1;
                    f = true;
                    break;
                }
            }

            if (!f) dp[i] = vec[vec.size() - 1] + 1;
        }
    }

    while (q--) {
        int m;
        scanf("%d", &m);
        printf("%d\n", dp[m] ? 1 : 2);
    }
    return 0;
}
