/* Persistent Segment Tree */
template <class S, S (*op)(S, S), S (*e)()>
struct persistentSegtree {
  long long l, r;
  S val;
  persistentSegtree<S, op, e>*left, *right;

  persistentSegtree(long long _l, long long _r)
      : persistentSegtree(_l, _r, e()) {}

  persistentSegtree(long long _l, long long _r, S _val)
      : l(_l), r(_r), val(_val) {
    left = right = nullptr;
  }

  persistentSegtree(vector<S>& a) : persistentSegtree(0, a.size() - 1, a) {}
  persistentSegtree(long long _l, long long _r, vector<S>& a) : l(_l), r(_r) {
    if (l == r) {
      val = a[l];
      return;
    }
    left = new persistentSegtree(l, (l + r) / 2, a);
    right = new persistentSegtree((l + r) / 2 + 1, r, a);
    val = op(left->val, right->val);
  }
  persistentSegtree(persistentSegtree* ln, persistentSegtree* rn)
      : l(ln->l), r(rn->r), val(op(ln->val, rn->val)), left(ln), right(rn) {}
  persistentSegtree(persistentSegtree* original) {
    l = original->l;
    r = original->r;
    val = original->val;
    left = original->left;
    right = original->right;
  }

  persistentSegtree* set(long long i, S x) {
    if (l == r) {
      return new persistentSegtree(i, i, x);
    }

    long long mid = (l + r) / 2;
    if (i <= mid) {
      if (left == nullptr) left = new persistentSegtree<S, op, e>(l, mid, e());
      return new persistentSegtree(left->set(i, x), right);
    } else {
      if (right == nullptr)
        right = new persistentSegtree<S, op, e>(mid + 1, r, e());
      return new persistentSegtree(left, right->set(i, x));
    }
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
/* End: Persistent Segment Tree */
