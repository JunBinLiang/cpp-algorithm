namespace Fenwick {
  const int SIZE = 200000 + 100;
  int tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}









//multiple fenwick tree
namespace Fenwick {
  const int SIZE = 100000 + 100;
  int tree[2][SIZE];
  void init(int n = 100000 + 100) {
    SIZE = n + 5;
    FOR(i, 0, n + 5) {
      tree[0][i] = 0;
      tree[1][i] = 0;
    }
  }

  void update(int which, int i, int val) {
    i++;
    while(i < SIZE){
      tree[which][i] += val;
      i += (i & -i);
    }
  }

  int pre(int which, int i) {
    int sum = 0;
    while(i > 0){
      sum += tree[which][i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int which, int i, int j) {
      return pre(which, j + 1) - pre(which, i);
  }
}
