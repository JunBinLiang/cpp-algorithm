struct node {
  int l, r;
  mutable int v; 
  node(ll l, ll r, ll v) : l(l), r(r), v(v) {} 
  bool operator<(const node &o) const { return l < o.l; } 
};

set<node> tree;

auto split(int pos) {
  auto it = tree.lower_bound(node(pos, 0, 0)); 
  if (it != tree.end() && it->l == pos) 
    return it;
  it--; 
  ll l = it -> l, r = it -> r, v = it -> v;
  tree.erase(it); 
  tree.insert(node(l, pos - 1, v)); 
  return tree.insert(node(pos, r, v)).first; 
}

void assign(int l, int r, int v) {
  auto end = split(r + 1), begin = split(l); // 顺序不能颠倒，否则可能RE
  tree.erase(begin, end); 
  tree.insert(node(l, r, v));
}
