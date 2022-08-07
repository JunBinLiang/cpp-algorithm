int mod = 998244353;
const double PI = acos(-1);
bool is[20];
int n, m;
const int md = 998244353;
const int gen = 3;
inline void add(int &a, int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
}
 
int pw(int a, int b) {
  int x = 1, step = 1 << 30;
  while (step > 0) {
    x = (long long)x * x % md;
    if (step & b) x = (long long)x * a % md;
    step >>= 1;
  }
  return x;
}
 
void fft(vector <int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    int j = 0;
    int x = i, y = n - 1;
    while (y > 0) {
      j = (j << 1) + (x & 1);
      x >>= 1;
      y >>= 1;
    }
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 1; len < n; len *= 2) {
    int root = pw(gen, (md - 1) / (2 * len));
    for (int i = 0; i < n; i += 2 * len) {
      int w = 1;
      for (int j = 0; j < len; j++) {
        int u = a[i + j];
        int v = (long long)a[i + j + len] * w % md;
        a[i + j] = u + v;
        if (a[i + j] >= md) a[i + j] -= md;
        a[i + j + len] = u - v;
        if (a[i + j + len] < 0) a[i + j + len] += md;
        w = (long long)w * root % md;
      }
    }
  }
}
 
vector<int> multiply(vector<int> a, vector<int> b) {
  int nn = 4;
  while (nn <= a.size() + b.size()) nn <<= 1;
  a.resize(nn);
  b.resize(nn);
  fft(a);
  fft(b);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * b[i] % md;
  reverse(++a.begin(), a.end());
  fft(a);
  int inv = pw(nn, md - 2);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * inv % md;
  a.resize(nn);
  return a;
}
