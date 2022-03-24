namespace Combination {
  int mod = 1000000007;
  ll fact[1000000 + 100];
  ll inv[1000000 + 100];
  
  ll modInverse(ll a, ll m) {
      ll m0 = m;
      ll y = 0, x = 1;
      if (m == 1)
          return 0;
      while (a > 1) {
          // q is quotient
          ll q = a / m;
          ll t = m;
          // m is remainder now, process
          // same as Euclid's algo
          m = a % m;
          a = t;
          t = y;
          // Update x and y
          y = x - q * y;
          x = t;
      }
      // Make x positive
      if (x < 0)
          x += m0;
      return x;
  }

  ll Pow(ll a, ll b, ll mo){
    ll an = 0;
    while(b) {
        if(b&1) an = (an + a) % mo;
        a = (a + a) % mo;
        b >>= 1;
    }
    return an % mo;
  }

  ll C(int n,int m) {
      return fact[n] * Pow(fact[n-m], mod - 2, mod) % mod * Pow (fact[m], mod - 2, mod) % mod;
  }

  void init() {
    fact[0] = 1;
    FOR(i, 1, 1000000 + 50) {
      fact[i] = fact[i - 1] * i;
      fact[i] %= mod;
    }

    inv[0] = inv[1]=1;
    for (int i=2;i < 1000000 + 50;i++){
        inv[i] = modInverse(i,mod) * inv[i-1];
        inv[i] %= mod;
    }
  }
}
