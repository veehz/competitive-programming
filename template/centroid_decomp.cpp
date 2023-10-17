#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
  vector<set<int>> original_adj;

  vector<set<int>> adj;
  vector<int> par, sz;

  vector<pair<int, int>> ancestors;

  CentroidDecomposition(const vector<set<int>> &_adj) : original_adj(_adj) {
    const auto n = _adj.size();
    adj.resize(n);
    par.resize(n);
    sz.resize(n);

    build(0, -1);
  }

  int dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : original_adj[u]) {
      if (v == p) continue;
      sz[u] += dfs(v, u);
    }
    return sz[u];
  }

  void getDist(int child, int centroid, int parent, int cur_dist = 1) {
    ancestors.push_back({child, cur_dist});
    for (auto v : original_adj[child]) {
      if (v == parent) continue;
      getDist(v, centroid, child, cur_dist + 1);
    }
  }

  int build(int u, int p) {
    int n = dfs(u, p);
    int centroid = dfs_centroid(u, p, n);

    for (auto v : original_adj[centroid]) {
      getDist(v, centroid, centroid);
    }

    if (p == -1) {
      p = centroid;
    }

    par[centroid] = p;
    adj[p].insert(centroid);

    for (auto v : original_adj[centroid]) {
      original_adj[v].erase(centroid);
      build(v, centroid);
    }
  }

  int dfs_centroid(int u, int p, int n) {
    for (auto v : original_adj[u]) {
      if (v == p) continue;
      if (sz[v] > n / 2) {
        return dfs_centroid(v, u, n);
      }
    }
    return u;
  }
};
