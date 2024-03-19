#include <bits/stdc++.h>
using namespace std;
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
 
	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		vector<vector<int>> adj(N+1), par(20, vector<int>(N+1, 0));
		vector<int> dp(N+1);
		for (int i = 1; i < N; i++) {
			int u, v; cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		function<void(int, int)> DFS = [&](int u, int p) {
			par[0][u] = p; for (int i = 1; i < 20; i++) par[i][u] = par[i - 1][par[i - 1][u]];
			dp[u] = dp[p] + 1;
			for (int& v : adj[u]) if (v != p) DFS(v, u);
		}; DFS(1, 0);
		auto LCA = [&](int u, int v) {
			if (dp[u] < dp[v]) swap(u, v);
			for (int i = 19; i >= 0; i--) if (dp[u] >= dp[v] + (1 << i)) u = par[i][u];
			if (u == v) return u;
			for (int i = 19; i >= 0; i--) if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
			return par[0][u];
		};
		int Q; cin >> Q;
		while (Q--) {
			int X, Y; cin >> X >> Y;
			int anc = LCA(X, Y);
			int len = dp[X] + dp[Y] - 2 * dp[anc];
			if (len % 2 == 0) cout << "No\n1 " << len + 1 << "\n";
			else cout << "Yes\n";
		}
	}
 
	return 0;
}
Language: C++17