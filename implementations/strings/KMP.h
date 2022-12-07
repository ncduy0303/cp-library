/**
 * Description: Finds all occurrences of a pattern string in a text string.
 * Prefix function computes longest proper prefix that matches suffix for each prefix.
 * Source: https://cp-algorithms.com/string/prefix-function.html
 * Verification: https://cses.fi/problemset/task/1753/
 * Time: O(n + m)
 */

vector<int> preprocess(const string &s) {
    int n = sz(s);
    vector<int> f(n); // longest prefix suffix function, f[0] = 0 by default
    for (int i = 1; i < n; i++) {
        int j = f[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = f[j - 1];
        }
        f[i] = j + (s[i] == s[j]);
    }
    return f;
}
 
int cntMatch(const string &s, const string &t) {
    string ts = t + "#" + s;
    int n = sz(t), nm = sz(ts);
    auto f = preprocess(ts);
    int cnt = 0;
    for (int i = n + 1; i < nm; i++) {
        cnt += (f[i] == n);
    }
    return cnt;
}