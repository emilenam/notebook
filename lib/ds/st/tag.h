#include "../../template.h"
/* -
name = "Tag Type"
[info]
description = "Tag operator type used for lazy propagation in lazy structures."
- */
struct Tag {
  ll b = 1, c = 0;
  void map(ll & x, int l, int r) const {
    x = (x * b % mod + c * (r - l) % mod) % mod;
  }
  void add(Tag & nu) const {
    b = b * nu.b % mod,
    c = (c * nu.b + nu.c) % mod;
  }
};
