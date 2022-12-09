/**
 * Description: Solves the single source shortest path problem for graphs with positive edges. Better for dense graphs.
 * Source: https://cp-algorithms.com/graph/dijkstra.html
 * Verification: https://www.spoj.com/problems/EZDIJKST/
 * Time: O(n^2)
 */

vector<ar<int,2>> adj[MAX_N];
ll dist[MAX_N];
int vis[MAX_N];

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);
    dist[s] = 0; 
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!vis[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }   
}
