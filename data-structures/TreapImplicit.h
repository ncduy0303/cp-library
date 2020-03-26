/**
 * Description: A treap that stores an array and supports O(log n) operations on it.
 * Source: https://cp-algorithms.com/data_structures/treap.html
 * Verification: https://www.spoj.com/problems/HORRIBLE/
 * Time: O(log n)
 */

struct Node {
    int priority, sz, val, ans, lazy;
    Node *l, *r;

    Node(int _val) : priority(rand() + (rand() << 15)), sz(1), val(_val), ans(val), lazy(0), l(NULL), r(NULL) {}
};
typedef Node* pNode;

int sz(pNode t) {
    return t ? t->sz : 0;
}

int ans(pNode t) {
    return t ? t->ans : 0;
}

void push(pNode t) {
    if (t && t->lazy) {
        t->val += t->lazy;
        t->ans += t->lazy * sz(t);
        if (t->l) t->l->lazy += t->lazy;
        if (t->r) t->r->lazy += t->lazy;
        t->lazy = 0;
    }
}

void calc(pNode t) {
    if (t) {
        push(t->l);
        push(t->r);
        t->sz = sz(t->l) + sz(t->r) + 1;
        t->ans = ans(t->l) + ans(t->r) + t->val;
    }
}

void split(pNode t, pNode &l, pNode &r, int pos, int add = 0) {
    if (!t) {
        l = r = NULL;
        return;
    }
    push(t);
    int curPos = add + sz(t->l);
    if (pos < curPos)
        split(t->l, l, t->l, pos, add), r = t;
    else
        split(t->r, t->r, r, pos, curPos + 1), l = t;
    calc(t);
}

void Merge(pNode &t, pNode l, pNode r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->priority > r->priority)
        Merge(l->r, l->r, r), t = l;
    else
        Merge(r->l, l, r->l), t = r;
    calc(t);
}

int query(pNode t, int l, int r) {
    pNode pl, pm, pr;
    split(t, pl, pm, l-1);
    split(pm, t, pr, r-l);
    int ret = t->ans;
    Merge(pm, pl, t);
    Merge(t, pm, pr);
    return ret;
}

void update(pNode t, int l, int r, int val) {
    pNode pl, pm, pr;
    split(t, pl, pm, l-1);
    split(pm, t, pr, r-l);
    t->lazy += val;
    Merge(pm, pl, t);
    Merge(t, pm, pr);
}
