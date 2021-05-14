#include <bits/stdc++.h>

using namespace std;

int n, x, y, z;
bool covered[60][60], table[60][60];
int deg[60][60];
set <pair <int, int> > wl;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main(){
    //freopen("table.inp", "r", stdin);
    //freopen("table.out", "w", stdout);

	scanf("%d %d %d %d", &n, &x, &y, &z); x--; y--; z--;

	int odd = (n*n + 1)/2;
	int even = n * n - odd;

	if (x & 1) even--;
	else odd--;

	if (y  & 1)even--;
	else odd--;

	if (z & 1) even--;
	else odd--;

	if (odd != even) return !printf("NIE\n");

	table[x/n][x % n] = table[y/n][y % n] = table[z/n][z % n]= true;
	for  (int i = 0; i<n; i++) {
		for (int j= 0;j<n; j++) {
			if (table[i][j]) continue;
			for (int k= 0;k<4; k++) {
				if (i + dx[k] >= 0 && i + dx[k] < n && j + dy[k] >= 0 && j + dy[k] < n) deg[i][j] += (not table[i + dx[k]][j + dy[k]]);
			}
			wl.insert(make_pair(deg[i][j], i * n + j));
		}
	}

	while (!wl.empty()) {
		int u = (*wl.begin()).second;
		int d = (*wl.begin()).first;
		x = u/n;
		y = u % n;
		int m = 10;
		int a = -1;
		int b = -1;

		wl.erase(make_pair(d, u));
		if (covered[x][y]) continue;
		for (int i = 0;i<4; i++) {
			if (x + dx[i] >= 0 && x +dx[i] < n && y + dy[i] >= 0 && y + dy[i] < n && not covered[x + dx[i]][y + dy[i]] && m >= deg[x + dx[i]][y + dy[i]]&& not table[x + dx[i]][y + dy[i]]) {
				m = deg[x + dx[i]][y + dy[i]];
				a = x + dx[i];
				b = y + dy[i];
			}
		}
		if (a == -1 || b == -1) continue;
		printf("%d %d\n", u + 1, a * n + b +1);
		deg[x][y] = deg[a][b] = 0;
		for (int i = 0;i<4; i++) {
			if (x+ dx[i] >=0 && x +dx[i] < n && y + dy[i] >= 0 && y + dy[i] < n && deg[x + dx[i]][y + dy[i]]) {
				wl.erase(make_pair(deg[x + dx[i]][y + dy[i]], (x + dx[i])*n + y + dy[i]));
				deg[x + dx[i]][y + dy[i]]--;
				wl.insert(make_pair(deg[x + dx[i]][y + dy[i]], (x + dx[i])*n + y + dy[i]));
			}
		}

		for (int i = 0;i<4; i++) {
			if (a+ dx[i] >=0 && a +dx[i] < n && b + dy[i] >= 0 && b + dy[i] < n && deg[a + dx[i]][b + dy[i]]) {
				wl.erase(make_pair(deg[a + dx[i]][b + dy[i]], (a + dx[i])*n + b + dy[i]));
				deg[a + dx[i]][b + dy[i]]--;
				wl.insert(make_pair(deg[a + dx[i]][b + dy[i]], (a + dx[i])*n + b + dy[i]));
			}
		}

		wl.erase(make_pair(m, a * n + b));
		covered[x][y] = covered[a][b] = true;
	}

	return 0;
}
