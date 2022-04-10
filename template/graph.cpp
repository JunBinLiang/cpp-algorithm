const int N = 10010, M = N * 2;
int h[N], e[M], w[M], ne[M], idx;

void add(int a, int b, int c)
{
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

void main() {
  memset(h, -1, sizeof h);
  idx = 0;

}
