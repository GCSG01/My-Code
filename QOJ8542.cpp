// Made by Bar.
#include <bits/stdc++.h>
using namespace std;

namespace {
	template <typename T> inline void read(T &x) {
		x = 0; T f = 1; char c = getchar();
		for(; !isdigit(c); c = getchar())
			if(c == '-') f = -1;
		for(;  isdigit(c); c = getchar())
			x = (x << 3) + (x << 1) + (c ^ 48);
		x *= f;
	}
}

const int N = 1E5 + 50;

int n, m, rt, d[N], vis[N], ans[N];
vector<int> g[N], l[N];
queue<int> que;

int cnt;
int solve(int cnt = 0) {
	for(; !que.empty(); ) {
		int u = que.front(); que.pop();
		++ cnt;
		if(d[u] != 1) {
			if(d[u] < 1) return u;
			for(int i = 1; i <= n; ++i) printf("0\n");
			exit(0);
		} 
		for(auto v : g[u]) {
			-- d[v]; ++ cnt;
			if(d[v] == 1) que.push(v);
		}
		for(auto v : l[u]) {
			-- d[v]; ++ cnt;
			if(d[v] == 1) que.push(v);
		}
	}
	if(cnt != n) {
		for(int i = 1; i <= n; ++i) printf("0\n"); 
		exit(0);
	}
}
void dfs(int u, int fa = -1) {
	ans[u] = 1;
	for(auto v : g[u]) 
		if(v != fa && !vis[v]) 
			dfs(v, u);
}
int main() {
	read(n), read(m);
	for(int u, v, i = 1; i < n; ++i) {
		read(u), read(v);
		g[u].push_back(v), g[v].push_back(u); 
		++ d[u], ++ d[v];
	}
	for(int a, b, i = 1; i <= m; ++i) {
		read(a), read(b);
		l[a].push_back(b);
		++ d[b];
		vis[a] = true;
	}
	for(int i = 1; i <= n; ++i) 
		if(d[i] == 1) que.push(i);
	rt = solve();
	dfs(rt);
	for(int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
