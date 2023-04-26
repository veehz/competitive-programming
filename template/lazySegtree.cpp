template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S),
          F (*composition)(F, F), F (*id)()>
struct lazySegtree {
  int _n;
  vector<S> d;
  vector<F> lz;
  lazySegtree() : lazySegtree(0) {}
  lazySegtree(int n) : lazySegtree(vector<S>(n, e())) {}
  lazySegtree(vector<S> a) : _n((int)a.size()), d(4 * (int)a.size()), lz(4 * (int)a.size(), id()) { build(a); }

  void build(const vector<S> &a, int v = 1, int tl = 0, int tr = -1) {
    if (tr == -1) tr = _n - 1;
    if (tl == tr) {
      d[v] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      build(a, 2 * v, tl, tm);
      build(a, 2 * v + 1, tm + 1, tr);
      d[v] = op(d[2 * v], d[2 * v + 1]);
    }
  }

  void apply(int v, F f) {
    d[v] = mapping(f, d[v]);
    lz[v] = composition(f, lz[v]);
  }

  void push(int v) {
    apply(2 * v, lz[v]);
    apply(2 * v + 1, lz[v]);
    lz[v] = id();
  }

  void update(int v) { d[v] = op(d[2 * v], d[2 * v + 1]); }

  void set(int pos, S val, int v = 1, int tl = 0, int tr = -1) {
    if (tr == -1) tr = _n - 1;

    if (tl == tr) {
      d[v] = val;
    } else {
      int tm = (tl + tr) / 2;
      push(v);
      if (pos <= tm) {
        set(pos, val, 2 * v, tl, tm);
      } else {
        set(pos, val, 2 * v + 1, tm + 1, tr);
      }
      update(v);
    }
  }

  /** Apply to [l,r] */
  void apply(int l, int r, F f, int v = 1, int tl = 0, int tr = -1) {
    if (tr == -1) tr = _n - 1;
    if (r < l) return;

    if (l == tl && r == tr) {
      apply(v, f);
    } else {
      push(v);
      int tm = (tl + tr) / 2;
      apply(l, min(r, tm), f, 2 * v, tl, tm);
      apply(max(l, tm + 1), r, f, 2 * v + 1, tm + 1, tr);
      update(v);
    }
  }

  /** a[l] x a[l+1] x ... x a[r] */
  S prod(int l, int r, int v = 1, int tl = 0, int tr = -1) {
    if (tr == -1) tr = _n - 1;
    if (r < l) return e();

    if (l == tl && r == tr) return d[v];

    push(v);
    int tm = (tl + tr) / 2;
    return op(prod(l, min(r, tm), 2 * v, tl, tm),
              prod(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr));
  }
};
