#include "../../template.h"
#include "split.h"
/* -
name = "Lazy Segment Tree"
[info]
time = "$O(log n)$"
- */
template <class T, auto op, class U> struct STLazy {
  int n; T e; U id; vec<T> s; vec<U> lz;
  STLazy(int n, T e, U id)
    : n(n), e(e), id(id), s(n<<1, e), lz(n, id) {}
  T query(int l, int r) { return query(l, r, 1, 0, n); }
  T query(int l, int r, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return e;
    if (l <= tl && tr <= r) return s[v];
    push(v, tl, tr);
    int tm = split(tl, tr);
    return op(query(l, r, v<<1, tl, tm),
              query(l, r, v<<1|1, tm, tr));
  }
  void upd(int l, int r, U u) { upd(l, r, u, 1, 0, n); }
  void upd(int l, int r, U u, int v, int tl, int tr) {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) { 
      u.map(s[v], tl, tr);
      if (v < n) lz[v].add(u);
      return;
    }
    push(v, tl, tr);
    int tm = split(tl, tr);
    upd(l, r, u, v<<1, tl, tm), upd(l, r, u, v<<1|1, tm, tr);
    s[v] = op(s[v<<1], s[v<<1|1]);
  }
  void push(int v, int tl, int tr) {
    int tm = split(tl, tr);
    upd(tl, tm, lz[v], v<<1, tl, tm);
    upd(tm, tr, lz[v], v<<1|1, tm, tr);
    lz[v] = id;
  }
  void build(vec<T>& a) {
    auto pw2 = bit_ceil(size(a));
    rep(i,0,n) s[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--) s[i] = op(s[i<<1], s[i<<1|1]);
  }
};
