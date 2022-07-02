const int MAX = 2000000 + 10;
int ids[300000 + 5];
int vals[100000 + 5];
struct Node {
  int l, r;
  int lid, rid;
  int mx;
} tree[MAX * 4];

int idx = 0;

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  int idx1 = idx;
  int idx2 = idx + 1;
  idx += 2;
  tree[id].lid = idx1;
  tree[id].rid = idx2;
  tree[idx1] = {l, mid, -1, -1, -1};
  tree[idx2] = {mid + 1, r,-1, -1, -1};
  build(idx1);
  build(idx2);
}

void update(int preId, int curId, int index, int val) {
  int l = tree[curId].l, r = tree[curId].r;
  if(l == r) {
    vals[l] = max(vals[l], val);
    tree[curId].mx = vals[l];
    return;
  }
  int mid = l + (r - l) / 2;
  if (index <= mid) {//update left
    tree[curId].rid = tree[preId].rid;
    tree[idx] = {tree[tree[preId].lid].l, tree[tree[preId].lid].r, -1, -1, -1};
    tree[curId].lid = idx;
    idx++;
    update(tree[preId].lid, tree[curId].lid, index, val);
  } else {//update right
    tree[curId].lid = tree[preId].lid;    
    tree[idx] = {tree[tree[preId].rid].l, tree[tree[preId].rid].r, -1, -1, -1};
    tree[curId].rid = idx;
    idx++;
    update(tree[preId].rid, tree[curId].rid, index, val);
  }
  tree[curId].mx = min(tree[tree[curId].lid].mx, tree[tree[curId].rid].mx);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = tree[id].lid, right = tree[id].rid;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}
