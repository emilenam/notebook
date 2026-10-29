#include "../../template.h"
/* -
name = "Iterative Segment Tree"
[info]
description = "Iterative segment tree, with point update and range queries. You can replace $s$ with a fast hashmap to get a dynamic segment tree."
time = "$O(log n)$"
- */
template <class T, auto op> struct SegmentTree {
  int n; T e; vec<T> s;
  SegmentTree(int n, T e) : n(n), e(e), s(n<<1, e) {}
  T query(int a, int b) { // [a, b)
    if(b<=a)return op(query(0,b), query(a,n));
    T ra = e, rb = e;
    for (a += n, b += n; a < b; a>>=1, b>>=1) {
      if (a&1) ra = op(ra, s[a++]);
      if (b&1) rb = op(s[--b], rb);
    }
    return op(ra, rb);
  }
  void upd(int i, T u) {
    for (i += n, s[i] = u; i>>=1;)
      s[i] = op(s[i<<1], s[i<<1|1]);
  }
  void build(vec<T> &a) {
    rep(i,0,n) s[i + n] = a[i];
    for (int i = n - 1; i >= 0; i--)
      s[i] = op(s[i<<1], s[i<<1|1]);
  }
};
