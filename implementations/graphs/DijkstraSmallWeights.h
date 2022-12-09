/**
 * Description: Solves the single source shortest path problem for graphs with small positive edges. Also known as Dial's algorithm.
 * Source: https://www.geeksforgeeks.org/dials-algorithm-optimized-dijkstra-for-small-range-weights/
 * Verification: https://www.spoj.com/problems/ADATRIP/
 * Time: O(n * maxW + m)
 */

int n, dist[MAX_N];
list<int>::iterator pos[MAX_N];
vector<ar<int,2>> adj[MAX_N];

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof dist);
    const int inf = dist[0];
    int i = 0;
    vector<list<int>> b(n * maxW + 1);
    dist[s] = 0;
    b[0].push_back(s);
    while (i < n * maxW) {
        int u = b[i].front(); b[i].pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                if (dist[v] != inf) b[dist[v]].erase(pos[v]);
                dist[v] = dist[u] + w;
                b[dist[v]].push_front(v);
                pos[v] = b[dist[v]].begin();
            }
        }
        while (i < n * maxW && b[i].empty()) i++;
    }
}
