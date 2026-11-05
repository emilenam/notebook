#include "../../template.h"
#include "split.h"
/* -
name = "Lazy Segment Tree"
[info]
time = "$O(log n)$"
description = "Requires struct U with map(T&,l,r) & add(U&,l,r,tl,tr)"
- */
template <class T, auto op, class U> struct SegmentTree {
  int n; T e; U id; vec<T> s; vec<U> lz;
  SegmentTree(int n, T e, U id)
    : n(n), e(e), id(id), s(n<<1, e), lz(n, id) {}
  T query(int l, int r) { return query(l, r, 1, 0, n); }
  T query(int l, int r, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v];
    int tm = split(tl, tr);
    push(v, tl, tr, tm);
    return op(query(l, r, v<<1, tl, tm),
              query(l, r, v<<1|1, tm, tr));
  }
  void upd(int l, int r, U u) { upd(l, r, u, 1, 0, n); }
  void upd(int l, int r, U& u, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) {
      //si no necesitas los rangos, puedes usar .add(u) directo
      U x = id; x.add(u, l, r, tl, tr);
      x.map(s[v], tl, tr);
      if (v < n) lz[v].add(x, tl, tr, tl, tr);
      return;
    }
    int tm = split(tl, tr);
    push(v, tl, tr, tm);
    upd(l, r, u, v<<1, tl, tm), upd(l, r, u, v<<1|1, tm, tr);
    s[v] = op(s[v<<1], s[v<<1|1]);
  }
  void push(int v, int tl, int tr, int tm) {
    upd(tl, tr, lz[v], v<<1, tl, tm);
    upd(tl, tr, lz[v], v<<1|1, tm, tr);
    lz[v] = id;
  }
  void build(vec<T>& a) {
    auto pw2 = bit_ceil(size(a));
    rep(i,0,n) s[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--) s[i] = op(s[i<<1], s[i<<1|1]);
  }
};
