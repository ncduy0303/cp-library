/**
 * Description: Decomposes graph into strongly connected components.
 * Source: https://cp-algorithms.com/graph/strongly-connected-components.html
 * Verification: https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/practice-problems/algorithm/a-walk-to-remember-qualifier2/
 * Time: O(n + m)
 */

#define MAX_N 100000

int n, sccCount;
bool visited[MAX_N];
vector<int> adj[MAX_N], adjr[MAX_N];
stack<int> stk;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v])
            dfs1(v);
    stk.push(u);
}

void dfs2(int u) {
    visited[u] = true;
    // do something with the node
    for (int v : adjr[u])
        if (!visited[v])
            dfs2(v);
}

void scc() {
    memset(visited, false, sizeof(visited));
    sccCount = 0;
    for (int i=0; i<n; i++)
        if (!visited[i])
            dfs1(i);

    memset(visited, false, sizeof(visited));
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        if (!visited[u]) {
            dfs2(u);
            sccCount++;
        }
    }
}
