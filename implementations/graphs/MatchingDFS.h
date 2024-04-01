/**
 * Description: Finds a maximum bipartite matching for a bipartite graph.
 * Source: Competitive Programming 3
 * Verification: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2079
 * Time: O(n * m), can be much faster with preprocessing heuristics
 */

#define MAX_N 100

int n, match[MAX_N];
bool visited[MAX_N], used[MAX_N];
vector<int> adj[MAX_N];

int aug(int u) {
    if (visited[u])
        return 0;
    visited[u] = true;
    for (int v : adj[u]) {
        if (match[v] == -1 || aug(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

int mcbm() {
    int ret = 0;
    memset(used, 0, sizeof(used));
    memset(match, -1, sizeof(match));
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (match[v] == -1) {
                match[v] = u;
                used[v] = true;
                ret++;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        memset(visited, false, sizeof(visited));
        ret += aug(i);
    }
    return ret;
}
