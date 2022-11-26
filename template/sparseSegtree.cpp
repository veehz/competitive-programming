/* Sparse Segment Tree */
template <class S, S (*op)(S, S), S (*e)()>
struct sparseSegtree {
  long long l, r;
  S val;
  sparseSegtree<S, op, e> *left, *right;
  sparseSegtree(long long l, long long r, S val) : l(l), r(r), val(val) {
    left = right = nullptr;
  }
  void set(long long i, S x) {
    if (l == r) {
      val = x;
      return;
    }
    long long mid = (l + r) / 2;
    if (i <= mid) {
      if (left == nullptr) left = new sparseSegtree<S, op, e>(l, mid, e());
      left->set(i, x);
    } else {
      if (right == nullptr)
        right = new sparseSegtree<S, op, e>(mid + 1, r, e());
      right->set(i, x);
    }
    val = op(left ? left->val : e(), right ? right->val : e());
  }
  S prod(long long ql, long long qr) {
    if (qr < l || r < ql) return e();
    if (ql <= l && r <= qr) return val;
    S sml = e(), smr = e();
    if (left != nullptr) sml = left->prod(ql, qr);
    if (right != nullptr) smr = right->prod(ql, qr);
    return op(sml, smr);
  }
};
/* End: Sparse Segment Tree */
