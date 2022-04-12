const int MAX = 120000;
struct Node {
  int l, r;
  int leftIdx = 0, rightIdx = 0;
  int sum;
} tree[MAX * 4];

int nodeIdx = 1;
void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  
  if(l == r) {
    tree[id].sum += val;
    return;
  }
  int mid = l + (r - l) / 2;
  if(index <= mid) {
    if(tree[id].leftIdx == 0) {
      tree[nodeIdx] = {l, mid, 0, 0, 0};
      tree[id].leftIdx = nodeIdx;
      nodeIdx++;
    }
    cout <<"left " <<  id << " " << l << " " << r <<" " << tree[id].leftIdx << endl;
    update(tree[id].leftIdx, index , val);
  } else {
    if(tree[id].rightIdx == 0) {
      tree[nodeIdx] = {mid + 1, r, 0, 0, 0};
      tree[id].rightIdx = nodeIdx;
      nodeIdx++;
    }
    cout <<"right " <<  id << " " << l << " " << r <<" " << tree[id].rightIdx << endl;
    update(tree[id].rightIdx, index , val);
  }

  tree[id].sum = 0;
  if(tree[id].leftIdx > 0) {
    tree[id].sum += tree[tree[id].leftIdx].sum;
  }
  if(tree[id].rightIdx > 0) {
    tree[id].sum += tree[tree[id].rightIdx].sum;
  }
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(id == 0) {
    return 0;
  }
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  if(e <= mid){
      return query(tree[id].leftIdx, s, e);
  } else if(s >= mid + 1) {
      return query(tree[id].rightIdx, s, e);
  } else {
    return query(tree[id].leftIdx, s, mid) +  query(tree[id].rightIdx, mid + 1, e);
  }
}
