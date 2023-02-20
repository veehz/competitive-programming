/* Segment Tree */
template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
  /* S op(S a, S b) {} -> Combine values */
  /* S e() {} -> Initial value (0) */
  int _n;
  vector<S> d;
  segtree() : segtree(0) {}
  explicit segtree(int n) : segtree(vector<S>(n, e())) {}
  explicit segtree(vector<S> v) : _n(int(v.size())) {
    d.assign(4 * _n, e());
    build(v);
  }
  void build(vector<S>& a, int v = 1, int tl = 0, int tr = -1) {
    if (tr == -1) tr = _n - 1;
    if (tl == tr) {
      d[v] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      d[v] = op(d[v * 2], d[v * 2 + 1]);
    }
  }
  void set(int pos, S new_val, int tl = 0, int tr = -1, int v = 1) {
    assert(0 <= pos && pos < _n);
    if (tr == -1) tr = _n - 1;
    if (tl == tr) {
      d[v] = new_val;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm)
        set(pos, new_val, tl, tm, v * 2);
      else
        set(pos, new_val, tm + 1, tr, v * 2 + 1);
      d[v] = op(d[2 * v], d[2 * v + 1]);
    }
  }
  S prod(int l, int r, int tl = 0, int tr = -1, int v = 1) {
    if (tr == -1) tr = _n - 1;
    if (r < l) return e();
    if (l == tl && r == tr) return d[v];
    int tm = (tl + tr) / 2;
    return op(prod(l, min(r, tm), tl, tm, 2 * v),
              prod(max(l, tm + 1), r, tm + 1, tr, 2 * v + 1));
  }
  // new - might have bugs
  size_t prod_lower_bound(S x, int tl = 0, int tr = -1, int v = 1,
                          S acc = e()) {
    if (tr == -1) {
      if (prod(0, _n - 1) <= x) return _n;
      tr = _n - 1;
    }
    if (tl == tr) return tl;
    int tm = (tl + tr) / 2;
    if (op(acc, d[2 * v]) < x)
      return prod_lower_bound(x, tm + 1, tr, 2 * v + 1, op(acc, d[2 * v]));
    else
      return prod_lower_bound(x, tl, tm, 2 * v, acc);
  }
  size_t prod_upper_bound(S x, int tl = 0, int tr = -1, int v = 1,
                          S acc = e()) {
    if (tr == -1) {
      if (prod(0, _n - 1) <= x) return _n;
      tr = _n - 1;
    }
    if (tl == tr) return tl;
    int tm = (tl + tr) / 2;
    if (op(acc, d[2 * v]) <= x)
      return prod_upper_bound(x, tm + 1, tr, 2 * v + 1, op(acc, d[2 * v]));
    else
      return prod_upper_bound(x, tl, tm, 2 * v, acc);
  }
};
/* End: Segment Tree */
