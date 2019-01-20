#include <bits/stdc++.h>

using namespace std;

const int N = 1e7 + 5;

int n;
stack <pair <int, int> > st;

int readInt(){
    char c;
    int ans = 0;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int main(){
    n = readInt();
    for (int i = 1; i <= n; i++) {
        int x, y;
        x = readInt(); y = readInt();

        bool ok = true;
        while (!st.empty()) {
            if (x - st.top().first <= st.top().second - y) {
                ok = false;
                break;
            }

            if (x - st.top().first <= y - st.top().second) st.pop();
            else break;
        }

        if (ok) st.push({x, y});
    }

    printf("%d", (int)st.size());
    return 0;
}
