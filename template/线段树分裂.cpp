#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2e5 + 10;

int n, m;
int a[N];
struct Node
{
    int l, r;
    LL v;
}tr[N * 40];
int root[N], idx;

void pushup(int u)
{
    tr[u].v = tr[tr[u].l].v + tr[tr[u].r].v;
}

int build(int l, int r)
{
   int p = ++ idx;
   if (l == r)
   {
       tr[p].v = a[r];
       return p;
   }
   int mid = l + r >> 1;
   tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
   pushup(p);
   return p;
}

void modify(int l, int r, int &u, int p, int x) //[p] += x;
{
    if (!u) u = ++ idx;
    tr[u].v += x;
    if (l == r) return ;
    int mid = l + r >> 1;
    if (p <= mid) modify(l, mid, tr[u].l, p, x);
    else modify(mid + 1, r, tr[u].r, p, x);
}

int split(int l, int r, int &u, int x, int y)
{
    int p = ++ idx;
    if (l >= x && r <= y)
    {
        tr[p] = tr[u];
        u = 0;
    }
    else
    {
        int mid = l + r >> 1;
        if (x <= mid) tr[p].l = split(l, mid, tr[u].l, x, y);
        if (y > mid) tr[p].r = split(mid + 1, r, tr[u].r, x, y);
        pushup(u);
        pushup(p);
    }

    return p;
}

void merge(int &x, int y)
{
    if (!x || !y) {
        x |= y;
        return ;
    }

    tr[x].v += tr[y].v;
    merge(tr[x].l, tr[y].l);
    merge(tr[x].r, tr[y].r);
}

LL query(int l, int r, int u, int x, int y)
{
    if (l >= x && r <= y) return tr[u].v;

    int mid = l + r >> 1;
    LL res = 0;
    if (x <= mid) res = query(l, mid, tr[u].l, x, y);
    if (y > mid) res += query(mid + 1, r, tr[u].r, x, y);

    return res;
}

int query(int l, int r, int u, int k)
{
    if (l == r) return r;
    int mid = l + r >> 1;
    LL cnt = tr[tr[u].l].v;
    if (k <= cnt) return query(l, mid, tr[u].l, k);
    else return query(mid + 1, r, tr[u].r, k - cnt);
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);

    root[1] = build(1, n);

    int last = 1;
    while (m -- )
    {
        int op, a, b, c;
        scanf("%d%d%d", &op, &a, &b);

        if (op == 0)
        {
            scanf("%d", &c);
            root[ ++ last] = split(1, n, root[a], b, c);
        }
        else if (op == 1)
            merge(root[a], root[b]);
        else if (op == 2) 
        {
            scanf("%d", &c);
            modify(1, n, root[a], c, b);
        }
        else if (op == 3)
        {
            scanf("%d", &c);
            printf("%lld\n", query(1, n, root[a], b, c));
        }
        else if (op == 4)
        {
            if (b > tr[root[a]].v) puts("-1");
            else printf("%d\n", query(1, n, root[a], b));
        }
    }

    return 0;
}

