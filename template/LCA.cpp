int LCA(int x,int y) {
  if(levels[x] < levels[y]){
    return LCA(y,x);
  }

  for(int i = 20; i>=0; i--) {
    if(f[x][i] != -1 && levels[f[x][i]] >= levels[y]) {
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
