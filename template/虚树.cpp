namespace VirtualTree {
  const int SIZE = 1e5 + 10;
  struct Graph { //general graph
    vector<int> g[SIZE];
    vector<pair<int, int>> edges;
    void add(int u, int v) {
      g[u].push_back(v);
      g[v].push_back(u);
      edges.push_back({u, v});
    }

    void clear() {
      for(auto& e : edges) {
        g[e.first].clear();
        g[e.second].clear();
      }
      edges.clear();
    }
  } graph;

  const int N = 1e5 + 10, M = 19;
  int d[N], dfn[N], f[N][M], id = 0;
  int stk[N];
  vector<int> g[N];

  void init() {
    memset(f, -1, sizeof f);
  }

  bool comp(int x, int y) {
    return dfn[x] < dfn[y];
  }

  void add(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void dfs(int pa, int root, int dep) {
    d[root] = dep;
    dfn[root] = id++;
    f[root][0] = pa;     
    for(int& nxt : g[root]) {
      if(nxt != pa) {
        dfs(root, nxt, dep + 1);
      }
    }
  }

  int LCA(int x,int y) {
    if(d[x] < d[y]){
      return LCA(y,x);
    }
    for(int i = M - 1; i >= 0; i--) {
      if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
        x = f[x][i];
      }
    }
    if(x == y) return x;
    for(int i = M - 1; i >= 0; i--) {
      if(f[x][i] != f[y][i]) {                    
        x = f[x][i];
        y = f[y][i];
      }
    }
    return f[x][0];
  }

  void preBuild(int n) {
    dfs(-1, 1, 0);
    for(int i = 1; i < M; i++) {
      for(int j = 1; j <= n; j++) {
        if(f[j][i - 1] != -1) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
      }
    }
  }
  
  //use stack to build the virtual tree:https://oi-wiki.org/graph/virtual-tree/#%E5%BC%95%E5%85%A5
  void build(vector<int>& a) {
    sort(a.begin(), a.end(), comp);
    int top = 0;
    stk[ top = 1 ] = 1;
    for(int i = 0; i < a.size(); i++) {
      int u = a[i];
      if(u == 1) continue;
      int lca = LCA(u, stk[top]);
      if(lca != stk[top]) {
        while(dfn[lca] < dfn[stk[top - 1] ]) {
          graph.add(stk[top - 1], stk[top]);
          top --;
        }
        if(dfn[lca] > dfn[stk[top - 1] ]) graph.add(lca, stk[top]), stk[top] = lca;
        else if(dfn[lca] == dfn[stk[top - 1] ]) {
            graph.add(lca, stk[top]), top --;
        }
      }
      stk[++ top] = u;
    }
    while(top > 1) {
      graph.add(stk[top - 1], stk[top]);
      top--;
    }
  }
}
