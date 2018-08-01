#include <bits/stdc++.h>

using namespace std;

class Data {
public:
    int b, c, id;

    Data (int b, int c, int id) {
        this->b = b;
        this->c = c;
        this->id = id;
    }
};

int n, k;
string s;
stack <Data> st;
stack <int> lastC, ans;

void input(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    cin >> s;
}

void solve(){
    for (int i = 0; i < n; i++) {
        if (lastC.empty()) lastC.push(0);
        if (st.empty()) {
            if (s[i] == 'b') st.push(Data(1, 0, i));
            else st.push(Data(0, 1, i));
        }
        else {
            if (s[i] == 'b') {
                Data val = st.top(); st.push(Data(val.b + 1, val.c, i));
                if (val.b + 1 - lastC.top() >= k && val.c >= 1) {
                    int cnt = k + 1;
                    while (cnt--) {
                        ans.push(st.top().id);
                        st.pop();
                    }
                    lastC.pop();
                }
            }
            else {
                Data val = st.top(); st.push(Data(val.b, val.c + 1, i));
                if (val.b - lastC.top() >= k && val.c >= 0) {
                    int cnt = k + 1;
                    while (cnt--) {
                        ans.push(st.top().id);
                        st.pop();
                    }
                }
                else lastC.push(val.b);
            }
        }
    }

    while (!st.empty()) {
        ans.push(st.top().id);
        st.pop();
    }

    for (int i = 0; i < n / (k + 1); i++) {
        int cnt = k + 1;
        while (cnt--) {
            printf("%d ", ans.top() + 1);
            ans.pop();
        }

        puts("");
    }
}

int main(){
    input();
    solve();
    return 0;
}
