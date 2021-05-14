#include <bits/stdc++.h>

using namespace std;

char c;
int n;
set <char> st;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> c >> n; st.insert(c);
    for (int i = 1; i <= n; i++) {
        char s1, s2;
        cin >> s1 >> s2;
        if (s2 == c) {
            c = s1;
            st.insert(c);
        }
    }

    cout << c << "\n" << st.size();
    return 0;
}
