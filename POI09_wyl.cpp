#include <bits/stdc++.h>

using namespace std;

const int N = 25;

int n, a[N], rem[N], pos[N], gett[N];
set <int> in;
vector <int> vec;
bool used[N];

int lcm (int x, int y) {
    return x * y / __gcd(x, y);
}

int LCM (int x) {
    int ans = 1;
    for (int i = 2; i <= x; i++) ans = lcm(ans, i);
    return ans;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]] = i, vec.push_back(i);
    for (int i = 1; i <= n; i++) gett[i] = LCM(i);
    //for (int i = 1; i <= n; i++) cout << pos[i] << " ";
    //cout << "\n";
    int pt = 0;
    for (int i = 1; i <= n; i++) {
        //assert(st.find(pos[a[i]]) != st.end());
        int cnt = 0;
        while (1) {
            if (used[pt]) {
                pt++;
                if (pt == vec.size()) pt = 0;
                continue;
            }
            cnt++;
            if (!used[pt] && vec[pt] == pos[i]) break;
            pt++;
            if (pt == vec.size()) pt = 0;
        }

        //cout << cnt << "\n";
        rem[n - i + 1] = cnt % (n - i + 1);
        //cout << st.size() << " " << rem[st.size()] << "\n";
        used[pt] = true;
        //for (auto it: st) cout << "SET " << it << "\n";
    }
    rem[1] = 0;
    //for (int i = 1; i <= n; i++) cout << rem[i] << "\n";

    int k = 0;
    for (int i = 1; i <= n; i++) {
        in.clear();
        int cnt = 0;
        while (k % i != rem[i]) {
            if (in.find(k % i) != in.end()) {
                cnt++;
                if (cnt == in.size()) return !printf("NIE");
            }
            else cnt = 0;

            in.insert(k % i);
            k += gett[i - 1];
        }
    }

    if (!k) k = gett[n];
    printf("%d", k);
    return 0;
}
