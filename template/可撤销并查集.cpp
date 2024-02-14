
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
const int N = 2e5+5;
int n,fa[N],rk[N];
struct edge{int u,v,w;} stk[N]; int top = 0; //记录操作的栈，u和v是连接的两个点，w代表连接之前u和v是否等秩。top是栈顶
 
inline void init(){FOR(i,1,n) fa[i]=i, rk[i]=1;} //初始化
int find(int x){return fa[x]==x ? x : find(fa[x]);} //递归找祖先，注意这里不能路径压缩
bool same(int u,int v){return find(u)==find(v);} //判断u和v祖先是否相等
void merge(int u,int v){ //连接u和v
	u = find(u), v = find(v); //把u和v赋值为自身的祖先
	if(u==v) return; //如果祖先相同，不做任何操作
	if(rk[u] > rk[v]) swap(u,v); //按秩调整u和v的父子关系，小连大
	fa[u] = v; //连接
	stk[++top] = {u, v, rk[u]==rk[v]}; //把连接记录在栈中
	if(rk[u]==rk[v]) rk[v]++; //如果等秩，v的秩+1
}
void undone(){ //撤销上一次连接
	int u = stk[top].u, v = stk[top].v, w = stk[top].w;
	rk[v] -= w; //如果连接前等秩，那么现在v的秩-1
	fa[u] = u; //取消u，v之间的连接
	top--;
}
