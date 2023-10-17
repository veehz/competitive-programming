/* Lazy Sparse Segment Tree (Unsure of correctness) */
template <class S, S (*op)(S, S, long long), S (*e)()>
struct lazysparseSegtree {
  /* S op(S a, S b, long long len) {} -> Combine values, op(a,b,len) = op(op(a,b,len-1),b,1) */
  /* S e() {} -> Initial value (0) */
  typedef long long ll;
  ll l, r;
  S val, flag;
  bool marked;
  lazysparseSegtree<S, op, e>*left, *right;
  lazysparseSegtree(ll _l, ll _r) : lazysparseSegtree(_l, _r, e()) {}
  lazysparseSegtree(ll _l, ll _r, S _val)
      : lazysparseSegtree(_l, _r, _val, false, e()) {}
  lazysparseSegtree(ll _l, ll _r, S _val, bool _marked, S _flag)
      : l(_l),
        r(_r),
        val(_val),
        marked(_marked),
        flag(_flag),
        left(nullptr),
        right(nullptr) {}

  void push() {
    if (marked) {
      if (left == nullptr)
        left = new lazysparseSegtree<S, op, e>(l, (l + r) / 2, e());
      if (right == nullptr)
        right = new lazysparseSegtree<S, op, e>((l + r) / 2 + 1, r, e());
      left->set(flag);
      right->set(flag);
      marked = false;
    }
  }

  void set(ll L, ll R, S x) {
    if (R < l || r < L) return;
    if (L <= l && r <= R) {
      set(x);
      return;
    }
    push();
    if (left == nullptr)
      left = new lazysparseSegtree<S, op, e>(l, (l + r) / 2, e());
    if (right == nullptr)
      right = new lazysparseSegtree<S, op, e>((l + r) / 2 + 1, r, e());
    left->set(L, R, x);
    right->set(L, R, x);
    val = op(left->val, right->val, 1);
  }

  void set(S x) {
    if (marked) {
      flag = op(flag, x, 1);
      val = op(val, x, r - l + 1);
    } else {
      marked = true;
      flag = x;
      val = op(val, x, r - l + 1);
    }
  }

  S prod(ll ql, ll qr) const {
    if (qr < l || r < ql) return e();
    if (ql <= l && r <= qr) return val;
    push();
    S sml = e(), smr = e();
    if (left != nullptr) sml = left->prod(ql, qr);
    if (right != nullptr) smr = right->prod(ql, qr);
    return op(sml, smr, 1);
  }

  S prod(ll q) const { return prod(q, q); }
};
/* End: Lazy Sparse Segment Tree */
