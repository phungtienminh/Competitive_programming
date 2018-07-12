#include <bits/stdc++.h>
using namespace std;

int n, b[30010], node[120010], s = 0; stack<int> ans;
void build_tree(int i, int l, int r) {
	if(l > r) return;
	if(l == r) {
		node[i] = 1;
		return;
	}
	int m = (l + r)/2;
	build_tree(i<<1, l, m);
	build_tree(i<<1|1, m+1, r);
	node[i] = node[i<<1] + node[i<<1|1];
}

int get(int i, int l, int r, int val) {
	if(l > r) return 0;
	if(l == r) {
		node[i] = 0;
		return l;
	}
	int m = (l + r)/2, a;
	if(node[i<<1|1] >= val) a = get(i<<1|1, m+1, r, val);
	else a = get(i<<1, l, m, val - node[i<<1|1]);
	node[i] = node[i<<1] + node[i<<1|1];
	return a;
}

int main() {
    //freopen("permutation.inp", "r", stdin);
    //freopen("permutation.out", "w", stdout);

	scanf("%d", &n); build_tree(1, 1, n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
		s += b[i];
		if(b[i] > i) return !printf("NIE\n");
	}
	for(int i = n-1; i >= 0; i--) ans.push(get(1, 1, n, b[i]+1));
	while(!ans.empty()) {
		printf("%d\n", ans.top());
		ans.pop();
	}
}
