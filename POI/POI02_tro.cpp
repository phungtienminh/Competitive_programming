#include <bits/stdc++.h>

using namespace std;

int readInt() {
    char c;
    int ans = 0;
    while (1) {
        c = getchar();
        if (c == '\n') break;

        ans = ans * 10 + (c - '0');
    }

    return ans;
}

int main(){
	//freopen("triagle.inp", "r", stdin);
	//freopen("triagle.out", "w", stdout);

	int n;
	vector <int> v;

	while (1) {
        n = readInt();
        if (n == 0) break;
		v.push_back(n);
	}

	sort(v.begin(), v.end());
	if (v.size() < 3) printf("NIE\n");
	else {
		for (int i = 2; i<v.size(); i++) {
			if (v[i - 2] + v[i - 1] > v[i]) {
				return !printf("%d %d %d\n", v[i - 2], v[i - 1], v[i]);
			}
		}

		printf("NIE\n");
	}
	return 0;
}
