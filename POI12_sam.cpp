#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int maxn = 5e5 + 5;

vector <int> v[N];
int a[maxn], n, k, p;
set <pair <int, int> > st;
bool onfloor[N];
int ans = 0;

int get (int pos, int val) {
    auto it = upper_bound(v[pos].begin(), v[pos].end(), val);
    if (it == v[pos].end()) return (int)1e9;

    return *it;
}

void input(){
    scanf("%d %d %d", &n, &k, &p);
    for (int i = 1; i <= p; i++) scanf("%d", &a[i]);
}

void solve(){
    memset(onfloor, 0, sizeof(onfloor));
    for (int i = 1; i <= p; i++) v[a[i]].push_back(i);
    for (int i = 1; i <= p; i++) {
        if (onfloor[a[i]]) {
            st.erase(st.find(make_pair(i, a[i])));
            st.insert(make_pair(get(a[i], i), a[i]));
        }
        else {
            if (st.size() == k) {
                auto it = *st.rbegin();
                onfloor[it.second] = false;
                st.erase(--st.end());
            }

            ans++;
            onfloor[a[i]] = true;
            st.insert(make_pair(get(a[i], i), a[i]));
        }
    }

    printf("%d", ans);
}

int main(){
    input();
    solve();
    return 0;
}
