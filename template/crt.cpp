//中国余数算法

namespace JBCRT {
  ll Exgcd(ll a,ll b,ll &x,ll &y){
    if( b == 0 ) { x = 1;y = 0; return a;}
    ll gcd = Exgcd(b,a%b,y,x);  //注意x和y的顺序
    y = y - a/b*x;
    return gcd;
}

ll qMul(ll a,ll b,ll mo){
  ll an = 0;
  while(b) {
      if(b&1) an =(an+a) % mo;
      a = (a+a) % mo;
      b>>=1;
  }
  return an % mo;
}

ll Crt(ve<int>& m, ve<int>& a) {
    int n = a.size(); 
    ll M = 1 ;
    for (int i = 0 ; i < n ; i ++) M *= m[i] ;
    ll X = 0 ;
    for (int i = 0 ; i < n ; i ++) {
      ll x, y ;
      ll M_i = M / m[i] ;
      Exgcd(M_i, m[i], x, y) ;
      X = (X + M_i * x * a[i]) % M ;
    }
    X = (X + M) % M;
    if(X == 0) X += M;
    return  X;
  }

  ll Excrt(ve<int>& mod, ve<int>& yu) {
    int n = mod.size();
    ll ans = yu[0], M = mod[0] ,t,  y;  
    for(int i = 1; i < n; i++){
        ll mi = mod[i], res = ((yu[i] - ans) % mi + mi) % mi;  
        ll gcd = Exgcd(M, mi,t,y);     
        if(res % gcd != 0) return -1;  
        t = qMul(t,res/gcd, mi);            
        ans += t * M;                               
        M = mi /gcd * M;                        
        ans = (ans % M + M) %M;                
    }
    if(ans == 0) ans += M;
    return ans;
  }
}
