/**
 * Description: Reduces DP on intervals with a monotonic cost of splitting array function from O(n^3) to O(n^2).
 * Condition: 
    - dp[i][j] = C[i][j] + min{i < k < j}(dp[i][k] + dp[k][j])
    - quadrangle inequality: C[a][c] + C[b][d] <= C[a][d] + C[b][c], a <= b <= c <= d
    - monotonicity: C[b][c] <= C[a][d], a <= b <= c <= d
 * Source: https://jeffreyxiao.me/blog/knuths-optimization
 * Verification: https://www.spoj.com/problems/BRKSTRNG/
 * Time: O(n^2)
 */

using ll = long long;

const int MAX_N = 5e3 + 5;

int n, opt[MAX_N][MAX_N];
ll dp[MAX_N][MAX_N];

ll cost(int l, int r);

void knuth() { 
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                if (dp[i][j] > dp[i][k] + dp[k + 1][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                    opt[i][j] = k;
                }
            }
            dp[i][j] += cost(i, j);
        }
    }
}