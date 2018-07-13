#include <bits/stdc++.h>

using namespace std;

const int N = 10005;
vector <pair <pair <double, double>, int> > v;

bool cmp (pair <pair <double, double>, int> a, pair <pair <double, double>, int> b) {
    return a.first.second * b.first.first < a.first.first * b.first.second;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        v.push_back(make_pair(make_pair(a, b), i));
    }

    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size(); i++) cout << v[i].second + 1 << "\n";
    return 0;
}
