int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }

  for(int i = 20; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i=20; i>=0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}
