#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, N1;
long long K;

int mx[N << 2], tag[N << 2];
unsigned char par[N << 2];
int head[N], tail[N], nxt[N];

#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)

inline void push_up(int p) {
    par[p] = par[ls] ^ par[rs];
    mx[p] = std::max(mx[ls], mx[rs]);
}

void build(int p, int l, int r) {
    tag[p] = 0;
    if (l == r) {
        mx[p] = l;
        par[p] = (N1 - l) & 1;
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    mx[p] = r;
    par[p] = par[ls] ^ par[rs];
}

inline void apply(int p, int l, int r, int v) {
    mx[p] = v;
    par[p] = ((r - l + 1) & 1) & ((N1 - v) & 1);
    tag[p] = v;
}

inline void push(int p, int l, int r) {
    if (!tag[p] || l == r) return;
    int v = tag[p];
    tag[p] = 0;
    apply(ls, l, mid, v);
    apply(rs, mid + 1, r, v);
}

int query(int p, int l, int r, int ql, int qr, int v) {
    if (qr < l || r < ql || mx[p] < v) return n + 1;
    if (ql <= l && r <= qr && tag[p] && tag[p] >= v) return l;
    if (l == r) return l;
    push(p, l, r);
    int res = query(ls, l, mid, ql, qr, v);
    if (res != n + 1) return res;
    return query(rs, mid + 1, r, ql, qr, v);
}

void range(int p, int l, int r, int ql, int qr, int v) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) return apply(p, l, r, v);
    push(p, l, r);
    range(ls, l, mid, ql, qr, v);
    range(rs, mid + 1, r, ql, qr, v);
    push_up(p);
}

inline void update(int L, int R, int c) {
    if (L > R) return;
    int p = query(1, 1, n, L, R, c);
    int ed = (p == n + 1 ? R : p - 1);
    if (L <= ed) range(1, 1, n, L, ed, c);
}

inline void add(int x, int i) {
    if (!head[x]) head[x] = tail[x] = i;
    else nxt[tail[x]] = i, tail[x] = i;
}
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    long long nn = inf.readLong();
    K = inf.readLong();

    if (nn < 1 || nn > 1000000)
        quitf(_fail, "invalid n in input");

    n = (int)nn;
    N1 = n + 1;

    long long lim = 1;
    while (lim <= n) lim <<= 1;

    if (ouf.seekEof())
        quitf(_wa, "empty user output");

    long long first = ouf.readLong();

    if (first == -1) {
        if (K >= lim)
            quitf(_ok, "Correct: no solution and k out of range.");

        bool officialNoSolution = false;
        if (!ans.seekEof()) {
            long long officialFirst = ans.readLong();
            officialNoSolution = (officialFirst == -1);
        }

        if (officialNoSolution)
            quitf(_ok, "Correct: no solution.");
        else
            quitf(_wa, "-1 is not acceptable on this test");
    }

    if (K >= lim)
        quitf(_wa, "k=%lld is impossible (>= %lld), sequence cannot be valid", K, lim);

    if (first < 0 || first > n)
        quitf(_wa, "a_1=%lld out of range [0,%d]", first, n);

    add((int)first, 1);

    for (int i = 2; i <= n; ++i) {
        if (ouf.seekEof())
            quitf(_wa, "too few numbers (expected %d, got %d)", n, i - 1);

        long long v = ouf.readLong();

        if (v < 0 || v > n)
            quitf(_wa, "a_%d=%lld out of range [0,%d]", i, v, n);

        add((int)v, i);
    }

    build(1, 1, n);

    int pre = par[1];
    long long xorAns = 0;

    for (int x = 0; x <= n; ++x) {
        if (!head[x]) {
            if (pre) xorAns ^= x;
            break;
        }

        int last = 0;
        for (int p = head[x]; p; p = nxt[p]) {
            if (last + 1 < p)
                update(last + 1, p, p);
            last = p;
        }

        if (last < n)
            update(last + 1, n, n + 1);

        int cur = par[1];
        if (pre ^ cur) xorAns ^= x;
        pre = cur;
    }
    if (xorAns == K)
        quitf(_ok, "Correct: xor of mex = %lld", K);
    else
        quitf(_wa, "xor of mex = %lld, expected %lld", xorAns, K);
}