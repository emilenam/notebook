const ll mod = 998244353;

inline ll mod_plus(ll a, ll b) { return (a + b) % mod; }

struct Tag {
  ll b = 1, c = 0;
  void map(ll & x, int l, int r) const {
    x = (x * b % mod + c * (r - l) % mod) % mod;
  }
  void add(Tag & nu, int l, int r, int tl, int tr) const {
    b = b * nu.b % mod,
    c = (c * nu.b + nu.c) % mod;
  }
};
