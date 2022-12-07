/**
 * Description: Array computing longest common prefix between the string and each of its suffixes.
 * Source: https://cp-algorithms.com/string/prefix-function.html
 * Verification: https://cses.fi/problemset/task/1753/
 * Time: O(n)
 */

vector<int> preprocess(const string &s) {
    int n = sz(s);
    vector<int> f(n); // f[0] = 0 by default
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) 
            f[i] = min(r - i + 1, f[i - l]);
        while (i + f[i] < n && s[f[i]] == s[i + f[i]]) 
            f[i]++;
        if (i + f[i] - 1 > r) 
            l = i, r = i + f[i] - 1;
    }
    return f;
}
