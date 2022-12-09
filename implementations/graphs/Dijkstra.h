/**
 * Description: Solves the single source shortest path problem for graphs with positive edges. Better for sparse graphs.
 * Source: own
 * Verification: http://codeforces.com/problemset/problem/20/C
 * Time: O(m log n)
 */

const int MAX_N = 100005;

vector<ar<int,2>> adj[MAX_N];
ll dist[MAX_N];

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<ar<ll,2>,vector<ar<ll,2>>,greater<ar<ll,2>>> pq;
    pq.push({dist[s] = 0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    } 
}
