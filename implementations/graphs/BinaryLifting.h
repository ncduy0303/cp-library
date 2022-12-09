/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: https://iq.opengenus.org/binary-lifting-k-th-ancestor-lowest-common-ancestor/
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(log n) query
 */

struct BinaryLift {
    int n, lg;
    vector<int> dep;
    vector<vector<int>> adj, par;
    
    BinaryLift(int _n) : n(_n), lg(__lg(n - 1) + 1), dep(n), adj(n), par(n, vector<int>(lg, -1)) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int s = 0) {
        dfs(s);
        for (int j = 1; j < lg; j++) {
            for (int i = 0; i < n; i++) {
                if (par[i][j - 1] != -1) {
                    par[i][j] = par[par[i][j - 1]][j - 1];
                }
            }
        }
    }

    void dfs(int u) {
        for (int v : adj[u]) {
            if (v == par[u][0]) continue;
            dep[v] = dep[u] + 1;
            par[v][0] = u;
            dfs(v);
        }
    }

    int kthAnc(int u, int k) {
        if (k > dep[u]) return -1;
        for (int j = 0; j < lg; j++) {
            if (k & (1 << j)) {
                u = par[u][j];
            }
        }
        return u;
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        u = kthAnc(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int j = lg - 1; j >= 0; j--) {
            if (par[u][j] != par[v][j]) {
                u = par[u][j];
                v = par[v][j];
            }
        }
        return par[u][0];
    }

    int dist(int u, int v) { 
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};
