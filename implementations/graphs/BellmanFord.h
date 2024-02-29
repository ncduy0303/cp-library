/**
 * Description: Solves the single source shortest path problem for graphs with negative edges.
 * Source: Competitive Programming 3
 * Verification: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=499
 * Time: O(n * m)
 */

#define MAX_N 100
#define ar array

int n, m, pre[MAX_N];
vector<ar<int,2>> adj[MAX_N];
ll dist[MAX_N];

bool bellmanFord(int s) {
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0; pre[s] = -1;
    for (int i = 0; i < n - 1; i++) {
        bool progress = false;
        for (int u = 0; u < n; u++) {
            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pre[v] = u;
                    progress = true;
                }
            }
        }
        if (!progress) break;
    }
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                return true;
            }
        }
    }
    return false;
}
 
vector<int> getCycle() {
    int node = -1;
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) { 
            if (dist[v] > dist[u] + w) { 
                node = v;
            }
        }
    }
    for (int i = 0; i < n; i++) node = pre[node];
    vector<int> cycle; cycle.push_back(node);
    for (int i = pre[node]; i != node; i = pre[i]) cycle.push_back(i); 
    cycle.push_back(node);
    reverse(cycle.begin(), cycle.end());
    return cycle;
}
