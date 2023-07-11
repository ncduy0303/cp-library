/**
 * Description: Offline algorithm for answering subarray queries. Optimal block size is n / sqrt(q).
 * Source: https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm
 * Verification: https://codeforces.com/contest/220/problem/B
 * Time: O((n + q) sqrt(n)) or O(n sqrt(q))
 */

const int BLOCK = 300;

struct Query {
    int l, r, idx;

    bool operator < (const Query &other) const {
        if (l / BLOCK == other.l / BLOCK) {
            if (r == other.r)
                return idx < other.idx;
            return l / BLOCK % 2 ? r > other.r : r < other.r;
        }
        return l < other.l;
    }
};

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
        // return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};

vector<int> mo(int q, const vector<int> &a, const vector<Query> &queries) {
    int ans = 0;

    auto add = [&] (int i) -> void {
        ans += a[i];
    };

    auto rem = [&] (int i) -> void {
        ans -= a[i];
    };

    sort(all(queries));
    int moLeft = 0, moRight = -1;
    vector<int> res(q);
    for (const Query &query : queries) {
        while (moLeft > query.l)
            add(--moLeft);
        while (moRight < query.r)
            add(++moRight);
        while (moLeft < query.l)
            rem(moLeft++);
        while (moRight > query.r)
            rem(moRight--);
        res[query.idx] = ans;
    }

    return res;
}
