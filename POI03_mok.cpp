#include <bits/stdc++.h>

using namespace std;

const int N = 55;
int a[N], b[N], temp_a[N], need[N], n;
bool dp[N][N][N][N];
int ans = 0x3f3f3f3f;

void solve() {
	queue <int> q;
	for (int i = 1; i<=n; i++) {
		q.push(a[i]);
	}

	q.push(0);
	dp[a[1]][a[2]][a[3]][a[4]] = true;
	while (!q.empty()) {
		for (int i = 1; i<=n; i++) {
			a[i] = q.front();
			q.pop();
		}
		int res = q.front(); q.pop();
		bool ok = true;

		for (int i = 1; i<=n; i++) {
			if (a[i] != need[i]) {
				ok = false;
				break;
			}
		}

		if (ok) {
			ans = res;
			return;
		}

		bool f = true;
		for (int i = 1; i<=n; i++) {
			if (a[i] != 0) {
				f = false;
				break;
			}
		}

		if (f) continue; //all buckets are empty

		for (int i = 1; i<=n; i++) {
			if (a[i] != 0) {
				for (int j = 1; j<=n; j++) {
					if (j == i) temp_a[j] = 0;
					else temp_a[j] = a[j];
				}
					//Type 3
				if (!dp[temp_a[1]][temp_a[2]][temp_a[3]][temp_a[4]]) {
					dp[temp_a[1]][temp_a[2]][temp_a[3]][temp_a[4]] = true;
					for (int k = 1; k<=n; k++) {
						q.push(temp_a[k]);
					}
					q.push(res + 1);
				}
			}
				//TYpe 1 and 2
			for (int j = 1; j<=n; j++) {
				if (j != i) {
					for (int k = 1; k<=n; k++) temp_a[k] = a[k];
					if (temp_a[j] < b[j] && temp_a[i] > 0) {
						int exchange = min(temp_a[i], b[j] - temp_a[j]);
						temp_a[j] += exchange;
						temp_a[i] -= exchange;

						if (!dp[temp_a[1]][temp_a[2]][temp_a[3]][temp_a[4]]) {
							dp[temp_a[1]][temp_a[2]][temp_a[3]][temp_a[4]] = true;
							for (int k = 1; k<=n; k++) {
								q.push(temp_a[k]);
							}
							q.push(res + 1);
						}
					}
				}
			}
		}
	}
}

int main(){
	//freopen("bucketwater.inp", "r", stdin);
	//freopen("bucketwater.out", "w", stdout);

	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(need, 0, sizeof(need));
	memset(temp_a, 0, sizeof(temp_a));
	for (int i = 1; i<=n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
		temp_a[i] = 0;
	}
	for (int i = 1; i<=n; i++) {
		scanf("%d", &need[i]);
	}

	memset(dp, 0, sizeof(dp));
	solve();

	if (ans == 0x3f3f3f3f) printf("NIE");
	else printf("%d", ans);
	return 0;
}
