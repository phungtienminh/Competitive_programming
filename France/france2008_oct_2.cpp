#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, m;
pair <int, int> monster[N], swords[N];
vector <pair <int, int> > vec;

bool cmp (pair <int, int> x, pair <int, int> y) {
    if (x.first != y.first) return x.first > y.first;
    return x.second > y.second;
}

bool cmp2 (pair <int, int> x, pair <int, int> y) {
    if (x.second != y.second) return x.second > y.second;
    return x.first > y.first;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &monster[i].first, &monster[i].second);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%d %d", &swords[i].first, &swords[i].second);

    for (int i = 1; i <= m; i++) {
        bool ok = true;
        for (int j = 1; j <= n; j++) {
            if (monster[j].first == 0) {
                if (monster[j].second > swords[i].first) {
                    ok = false;
                    break;
                }
            }
            else {
                if (monster[j].second > swords[i].second) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) return !printf("%d", 1);
    }

    sort(swords + 1, swords + m + 1, cmp); vec.push_back(swords[1]);
    sort(swords + 1, swords + m + 1, cmp2); vec.push_back(swords[1]);
    if (vec[0].first == vec[1].first && vec[0].second == vec[1].second) vec.pop_back();

    for (int i = 1; i <= n; i++) {
        bool ok = false;
        for (int j = 0; j < vec.size(); j++) {
            if (monster[i].first == 0) {
                if (monster[i].second <= vec[j].first) ok = true;
            }
            else {
                if (monster[i].second <= vec[j].second) ok = true;
            }
        }

        if (!ok) return !printf("%d", -1);
    }

    printf("%d", (int)vec.size());
    return 0;
}
