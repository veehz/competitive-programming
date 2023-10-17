template <class S, class AnySegtree, S (*op)(S, S), S (*e)(),
          S (*invert_dir)(S)>
struct HLD {
  int n;
  AnySegtree st;
  vector<int> par, depth, heavy, head, pos;

  int cur_pos;

  HLD(const vector<vector<int>>& _adj, const vector<S>& init = {})
      : n(_adj.size()),
        st(n),
        par(n),
        depth(n),
        heavy(n, -1),
        head(n),
        pos(n),
        cur_pos(0) {
    dfs(0, _adj);
    decompose(0, 0, _adj);
    if (!init.empty()) {
      for (int i = 0; i < n; i++) {
        st.set(pos[i], init[i]);
      }
    }
  };

  int dfs(int u, const vector<vector<int>>& _adj) {
    int cur_sz = 1;
    int max_ch_sz = 0;
    for (auto v : _adj[u]) {
      if (v == par[u]) continue;
      par[v] = u, depth[v] = depth[u] + 1;
      int v_sz = dfs(v, _adj);
      cur_sz += v_sz;
      if (v_sz > max_ch_sz) max_ch_sz = v_sz, heavy[u] = v;
    }
    return cur_sz;
  }

  void decompose(int u, int h, const vector<vector<int>>& _adj) {
    head[u] = h, pos[u] = cur_pos++;
    if (heavy[u] != -1) decompose(heavy[u], h, _adj);
    for (auto& v : _adj[u]) {
      if (par[u] == v || heavy[u] == v) continue;
      decompose(v, v, _adj);
    }
  }

  S query(int u, int v) {
    S ures = e(), vres = e();
    for (; head[u] != head[v]; v = par[head[v]]) {
      if (depth[head[u]] > depth[head[v]]) swap(u, v), swap(ures, vres);
      vres = op(st.prod(pos[head[v]], pos[v]), vres);
    }

    if (depth[u] > depth[v]) swap(u, v), swap(ures, vres);
    // u -> v
    S query = st.prod(pos[u], pos[v]);
    return op(op(invert_dir(ures), query), vres);
  }
};
