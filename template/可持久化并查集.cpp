//https://www.luogu.com.cn/problem/P3402

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 2e5 + 10;
struct Node{
    int l, r, val;
} tr[N * 40 * 2];
//idx负责给树中的每个结点分配一个编号
//tot负责给树中的每个结点赋一个值
//rootfa[i]记录的是第i个版本的并查集中的集合号(祖宗结点)
//rootdep[i]记录的是第i个版本的并查集中的集合号的深度(祖宗结点的深度)
int idx, tot, rootfa[N], rootdep[N];
int n, m;

void build(int l, int r, int &u) {
  u = ++idx;    //给结点u分配一个编号
  if(l == r) {   
    tr[u].val = ++tot;    //给结点u赋一个值
    return;
  }
  int mid=(l + r) >> 1;
  build(l, mid, tr[u].l);   //递归创建左子树
  build(mid+1, r, tr[u].r); //递归创建右子树
}

void modify(int l, int r, int ver, int &u, int pos, int val) {
  u = ++idx;    //给当前节点u分配一个编号
  //当前版本u继承上一个版本ver
  tr[u] = tr[ver];
  if(l == r)//到了叶子结点
  {
    tr[u].val = val;  //将结点u的值修改为val
    return;
  }
  int mid = (l + r) >> 1;
  if(pos <= mid)    //递归去修改左子树
    modify(l, mid, tr[ver].l, tr[u].l, pos, val);
  else            //递归去修改右子树
    modify(mid+1, r, tr[ver].r, tr[u].r, pos, val);
}

int query(int l,int r, int u, int pos)
{
  if(l == r)//到了叶子结点 返回该节点的值
    return tr[u].val;
  int mid = (l + r) >> 1;
  if(pos <= mid)    //递归查询左子树
    return query(l, mid, tr[u].l, pos);
  else            //递归查询右子树
    return query(mid + 1, r, tr[u].r, pos);
}

//要找到第ver个版本中x的父亲
int find(int ver, int x)
{
  //去第ver个版本的线段树(其根节点是rootfa[ver])中查询位置x上的值
  int fx = query(1, n, rootfa[ver], x);
  if(x != fx)
    x = find(ver, fx); //不能进行路径压缩
  return x;
}

//将第ver个版本中的集合x和集合y
void merge(int ver,int x,int y) {
  //传进来的ver是一个全新的版本 我们在op=1时执行了merge操作
  //比如ver=0,我们已经构建好了 然后传进来ver=1 
  //执行merge操作那么此时ver=1这个全新的版本中并没有任何东西 
  //因为我们在执行merge之前并没有弄过rootfa[ver]=rootfa[ver-1] 所以它现在是空的
  //因此如果我们想要寻找当前ver版本中结点x的父亲 那么可以去上一个版本ver-1中找x的父亲
  x = find(ver - 1, x);    //找到x所在的集合号
  y = find(ver - 1, y);    //找到y所在的集合号
  if(x == y)//在同一个集合中
  {
    //当前版本直接继承上一个版本即可
    //其实就是虽然没有把x和y合并  但是由于我们执行了merge这次操作
    //既然是操作 那么就会产生新版本  所以需要当前版本直接继承上一个版本
    rootfa[ver] = rootfa[ver - 1];
    rootdep[ver] = rootdep[ver - 1];
  }
  else
  {
    int depx = query(1, n, rootdep[ver - 1], x);   //求出x的深度
    int depy = query(1, n, rootdep[ver - 1], y);   //求出y的深度
    if(depx < depy)
    {
      //将深度小的x合并到深度大的y上   含义就是fa[x]=y
      modify(1, n, rootfa[ver - 1], rootfa[ver], x, y);
      //将深度小的x合并到深度大的y上不会导入深度有变化
      //因此当前版本的深度直接继承上一个版本的深度即可
      rootdep[ver] = rootdep[ver - 1];
    }
    else if(depy < depx)
    {
      //将深度小的y合并到深度大的x上   含义就是fa[y]=x
      modify(1, n, rootfa[ver-1], rootfa[ver], y, x);
      //将深度小的x合并到深度大的y上不会导入深度有变化
      //因此当前版本的深度直接继承上一个版本的深度即可
      rootdep[ver] = rootdep[ver - 1];
    }
    else    //这两个集合的深度相等
    {
      //将x合并到y
      modify(1, n, rootfa[ver - 1], rootfa[ver], x, y);
      //此时y的深度多1
      modify(1, n, rootdep[ver - 1], rootdep[ver], y, depy + 1);
    } 
  }
}

int main() {
  scanf("%d%d", &n, &m);
  build(1, n, rootfa[0]);
  for(int i = 1; i <= m; i++) {
    int op, a, b;
    scanf("%d", &op);
    if(op==1)   //合并两个集合a,b
    {
      scanf("%d%d", &a, &b);
      merge(i, a, b);
    }
    else if(op==2)//回到第k次操作
    {
      int k;
      scanf("%d",&k);
      //将当前版本追溯到第k个版本
      rootfa[i] = rootfa[k];
      rootdep[i] = rootdep[k];
    }
    else if(op == 3)//询问a,b是否在同一个集合中
    {
      scanf("%d%d",&a,&b);
      //询问也是一次操作 但是它没有对上一个版本进行修改
      //所以执行询问时 也算一次操作  那么当前版本直接继承上一个版本即可
      rootfa[i] = rootfa[i - 1];
      rootdep[i] = rootdep[i - 1];
      a = find(i, a);
      b = find(i, b);
      if(a == b)
        puts("1");
      else
        puts("0");
    }
  }
  return 0;
}
