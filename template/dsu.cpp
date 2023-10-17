struct dsu {
  vector<int> par, sz;
  int n;
  dsu(int _n) : n(_n) {
    par.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++) {
      par[i] = i;
      sz[i] = 1;
    }
  }
  int find(int x) {
    if (x == par[x]) return x;
    return par[x] = find(par[x]);
  }
  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    par[y] = x;
    sz[x] += sz[y];
  }

  vector<int> roots;
  void init_roots() {
    roots.clear();
    for (int i = 0; i < n; i++) {
      if (par[i] == i) roots.push_back(i);
    }
  }

  map<int, int> mp;
  void map_roots() {
    mp.clear();
    for (size_t i = 0; i < roots.size(); i++) {
      mp[roots[i]] = i;
    }
  }

  void index_compression() {
    init_roots();
    map_roots();
  }
  int compress(int x) { return mp[find(x)]; }
  int decompress(int x) const { return roots[x]; }
};
