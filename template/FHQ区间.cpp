#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


unsigned long long seed = 1;
const int N = 500010 + 100;
struct FHQ {
    struct {
      int l, r;  // 左右孩子
      int val;   // 节点权值
      int rnd;   // 随机值
      int size;  // 子树大小

      int rev_tag;  // 翻转延迟标记
      int cov_tag;  // 覆盖延迟标记
      int cov_val;  // 覆盖更新的值

      ll sum;   // 子树的区间和
      ll ls;  // 区间最大前缀和
      ll rs;  // 区间最大后缀和
      ll ms;  // 子树内最大的区间和
    } tr[N];
    
    int gctop = -1, stk[N];
    int root = 0, n = 0;  // 根节点, 最新节点的下标
                          //
    inline int _rand() {
        seed *= 260817;
        return int(seed);
    }

    void gc(int u) {
      if(!u) return;
      stk[++gctop] = u;
      gc(tr[u].l);
      gc(tr[u].r);
    }

    // 创建一个新节点
    int newnode(int v) {
      int id = -1;
      if(gctop >= 0) {
        id = stk[gctop--];
      } else {
        id = ++n;
      }
      tr[id].val = tr[id].sum = tr[id].ms = v;
      tr[id].ls = tr[id].rs = max(0, v);
      tr[id].rnd = _rand();
      tr[id].size = 1;
      tr[id].rev_tag = tr[id].cov_tag = 0;
      tr[id].l = tr[id].r = 0;
      return id;
    }

    void rev(int u) {
      if(!u) return;
      tr[u].rev_tag ^= 1;
      swap(tr[u].l, tr[u].r);
      swap(tr[u].ls, tr[u].rs);
    }

    void cover(int u, int c) {
      if(!u) return;
      tr[u].cov_tag = 1;
      tr[u].cov_val = c;
      tr[u].val = c;
      tr[u].sum = (c + 0ll) * tr[u].size;
      tr[u].ls = tr[u].rs = max(tr[u].sum, 0ll);
      tr[u].ms = max(c + 0ll, tr[u].sum); //single, or take all
      tr[u].rev_tag = 0;
    }

    void pushup(int p) { 
      tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1; 
      tr[p].sum = tr[tr[p].l].sum + tr[tr[p].r].sum + tr[p].val;
      tr[p].ms = max(tr[tr[p].l].ms, tr[tr[p].r].ms);
      tr[p].ms = max(tr[p].ms, tr[tr[p].l].rs + tr[p].val + tr[tr[p].r].ls);
      tr[p].ls = max(tr[tr[p].l].ls, tr[tr[p].l].sum + tr[p].val + tr[tr[p].r].ls);
      tr[p].rs = max(tr[tr[p].r].rs, tr[tr[p].r].sum + tr[p].val + tr[tr[p].l].rs);
    }

    void pushdown(int p) {
      if(tr[p].rev_tag) {
        rev(tr[p].l);
        rev(tr[p].r);
        tr[p].rev_tag = 0;
      }
      if(tr[p].cov_tag) {
        cover(tr[p].l, tr[p].cov_val);
        cover(tr[p].r, tr[p].cov_val);
        tr[p].cov_tag = 0;
      }
    }

  //split by size
  void split(int u, int sz, int &x, int &y) {
    if (!u) {
      x = y = 0;
      return;
    }
    pushdown(u);
    if(tr[tr[u].l].size < sz) {
      x = u;
      split(tr[u].r, sz - tr[tr[u].l].size - 1, tr[u].r, y);
    }
    else {
      y = u;
      split(tr[u].l, sz, x, tr[u].l);
    }
    pushup(u);
  }


  // 按堆的随机值合并两颗子树, 返回合并后的根
  // 要求 x 树所有节点的 val 要 <= y 树所有节点的 val 值
  int merge(int x, int y) {
    if (!x || !y) return x + y;  // 存在空树的情况
    if (tr[x].rnd < tr[y].rnd) {
      // 应把 x 放上面, 先递归合并 x 的右子树 r 和 y 得到新树 z
      // 因为 x 权值更小, 所以把 z 作为 x 的右孩子
      pushdown(x);
      tr[x].r = merge(tr[x].r, y);
      pushup(x);
      return x;
    } else {
      pushdown(y);
      tr[y].l = merge(x, tr[y].l);
      pushup(y);
      return y;
    }
  }

  // 插入一个值
  void insert(int v) {
    // 按 v 分裂, 找到插入点 x <=v < y
    int x, y;
    split(root, v, x, y);
    // 新建节点
    int z = newnode(v);
    // 依次合并 x, z 和 y (权值 val 也满足如此顺序)
    root = merge(merge(x, z), y);
  }

  // 删除一个值
  void del(int v) {
    int x, y, z;
    // 先找到 v 的分割点 => x <= v < z
    split(root, v, x, z);
    // 再按 v-1 分裂 x 树 => x <= v-1 < y <= v
    split(x, v - 1, x, y);
    // y 就是值等于 v 的节点, 删除它
    // 如果找不到 v, y 就是空树, 其左右孩子都是 0, 不影响
    y = merge(tr[y].l, tr[y].r);
    // 再把 x, y, z 合并起来
    root = merge(merge(x, y), z);
  }

  // 查找排名, 满足 < v 的个数+1
  int rank(int v) {
    int x, y;
    split(root, v - 1, x, y);
    int ans = tr[x].size + 1;
    root = merge(x, y);
    return ans;
  }

  // 从子树 p 找第 k 小
  int topk(int p, int k) {
    int lsz = tr[tr[p].l].size;
    if (k == lsz + 1) return tr[p].val;
    if (k <= lsz) return topk(tr[p].l, k);
    return topk(tr[p].r, k - lsz - 1);
  }

  // 前驱, 严格 <v 的值
  int get_pre(int v) {
    int x, y;
    split(root, v - 1, x, y);
    int ans = topk(x, tr[x].size);
    root = merge(x, y);
    return ans;
  }

  // 后继, 严格 > v 的值
  int get_suc(int v) {
    int x, y;
    split(root, v, x, y);
    int ans = topk(y, 1);
    root = merge(x, y);
    return ans;
  }
};


int main() {
    
  FHQ t;
  t.tr[0].ms = -1e18; //处理0，处理pushup时为leaf的情况 
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
      int v;
      scanf("%d", &v);
      t.root = t.merge(t.root, t.newnode(v));
  }
  
  char op[20];
  while (m -- )
  {
    scanf("%s", op);
    if (!strcmp(op, "INSERT")) {
      int pos, tot;
      scanf("%d%d", &pos, &tot);
      if(!pos) {
        vector<int> vals;
        for(int i = 0; i < tot; i++) {
          int v;
          scanf("%d", &v);
          vals.push_back(v);
        }
        for(int i = vals.size() - 1; i >= 0; i--) {
            t.root = t.merge(t.newnode(vals[i]), t.root);
        }
      } else {
        int x, y;
        t.split(t.root, pos, x, y);
        for(int i = 0; i < tot; i++) {
          int v;
          scanf("%d", &v);
          x = t.merge(x, t.newnode(v));
        }
        t.root = t.merge(x, y);
      }
    }
    else if (!strcmp(op, "DELETE")) {
      int pos, tot;
      scanf("%d%d", &pos, &tot);
      int x, y, z;
      t.split(t.root, pos - 1, x, y);
      t.split(y, tot, y, z);
      t.gc(y); //garbage collection
      t.root = t.merge(x, z);
      
    }
    else if (!strcmp(op, "MAKE-SAME")) {
      int pos, tot, v;
      scanf("%d%d%d", &pos, &tot, &v);
      int x, y, z;
      t.split(t.root, pos - 1, x, y);
      t.split(y, tot, y, z);
      t.cover(y, v);
      t.root = t.merge(x, t.merge(y, z));
    }
    else if (!strcmp(op, "REVERSE")) {
      int pos, tot, v;
      scanf("%d%d%d", &pos, &tot, &v);
      int x, y, z;
      t.split(t.root, pos - 1, x, y);
      t.split(y, tot, y, z);
      t.rev(y);
      t.root = t.merge(x, t.merge(y, z));
    }
    else if (!strcmp(op, "GET-SUM")) {
      int pos, tot, v;
      scanf("%d%d%d", &pos, &tot, &v);
      int x, y, z;
      t.split(t.root, pos - 1, x, y);
      t.split(y, tot, y, z);
      printf("%lld\n", t.tr[y].sum);
      t.root = t.merge(x, t.merge(y, z));
    }
    else {
      printf("%lld\n", t.tr[t.root].ms);
    }
  }
  return 0;
}
