struct Centroid {
int n; //number of node
// for building
int root;
vector<int> sub, par;
vector<bool> mark;
// vector<int> adj[MAXN]        (just keep this outside)
// for query, update... stores subtree answer in most problems
vector<int> ans;// ans[u] stores optimal answer (among all paths in orig tree from u to some node in centroid tree) 
    // should have lca structure ready
void init(int x) {//1 indexed
  n = x;
  mark.assign(n + 1, 0), sub.assign(n + 1, 0), par.assign(n + 1, -1);
  ans.assign(n + 1, inf);
}
int find_centroid(int r) {
  function<void(int, int)> ss = [&](int u, int p) {
  sub[u] = 1;
  for(auto v : adj[u])
    if(v != p and !mark[v]) ss(v, u), sub[u] += sub[v];
  };
  ss(r, 0);
  int cen = 0, s = sub[r];
  function<void(int, int)> dfs = [&](int u, int p) {
    if(cen)    return;
    bool now = (sub[r] - sub[u] <= sub[r]/2);
    for(auto v : adj[u])
    if(v != p and !mark[v] and cen == 0)
    now = (now and sub[v] <= sub[r]/2);
    if(now) {cen = u; return;}
    for(auto v : adj[u])
    if(v != p and !mark[v] and cen == 0) dfs(v, u);
  };
  dfs(r, 0); mark[cen] = 1;
  return cen;
};
void build() {
  int cen = find_centroid(1);     //note
  root = cen;
  function<void(int, int)> dfs = [&](int u, int p) {
    for(auto v : adj[u]) {
      if(!mark[v]) {
        int cen2 = find_centroid(v);
        par[cen2] = u; dfs(cen2, u);
      }
    }
  };
  dfs(root, 0);
}
void update(int u, int x) {
  while(u != -1) {
    // update value of ans[u] if required
    u = par[u];
  }
}
int query(int u) {
  int x;
  while(u != -1) {
    // try to update value of x using ans[u]
    u = par[u];
  }
  return x;
}
}centroid;