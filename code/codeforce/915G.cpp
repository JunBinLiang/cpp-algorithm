#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;
const int mod=1e9+7;
inline int read(){
	char c=getchar();int t=0,f=1;
	while((!isdigit(c))&&(c!=EOF)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)&&(c!=EOF)){t=(t<<3)+(t<<1)+(c^48);c=getchar();}
	return t*f;
}
int n,k;
int mu[maxn],p[maxn],cnt,vis[maxn];
void get(){
	mu[1]=1;
	for(int i=2;i<=k;i++){
		if(!vis[i]){
			p[++cnt]=i;mu[i]=-1;
		}
		for(int j=1;j<=cnt&&1ll*i*p[j]<=k;j++){
			vis[i*p[j]]=1;mu[i*p[j]]=mu[i]*mu[p[j]];
			if(i%p[j]==0){
				mu[i*p[j]]=0;break;
			}
		}
	}
}
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;b>>=1;
	}
	return ans;
}
int pw[maxn],b[maxn*2];
int main(){
	n=read(),k=read();
	for(int i=1;i<=k;i++)pw[i]=ksm(i,n);
	get();
	for(int x=1;x<=k;x++){
		for(int i=1;i*x<=k;i++){
			b[i*x]=(b[i*x]+1ll*pw[i]*(mod+mu[x])%mod)%mod;
			b[i*x]=(b[i*x]-1ll*pw[i-1]*(mod+mu[x])%mod)%mod;
			if(b[i*x]<0)b[i*x]+=mod;
		}
	}
	int ans=0;
	for(int i=1;i<=k;i++){
		b[i]=(b[i]+b[i-1])%mod;
		ans=(ans+(b[i]^i)%mod)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
