#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+5,mod=998244353;
int t[N],b[N],n,inv2;
int sg(int x){
	int len=1,sum=0;
	while(sum<x){
		sum+=len;
		if(sum>=x)return x-sum+len;
		len<<=1;
	}
}
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
void FWT(int *a,int flag){
	for(int i=1;i<n;i<<=1)
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0;k<i;k++){
                int a1=a[j+k],a2=a[j+k+i];
                a[j+k]=(a1+a2)%mod,a[j+k+i]=(a1-a2+mod)%mod;
                if(flag==-1)
                    a[j+k]=a[j+k]*inv2%mod,a[j+k+i]=a[j+k+i]*inv2%mod;
            }
    return ;
}
void mul(int *x,int *y){
    for(int i=0;i<=n;i++)
        x[i]=x[i]*y[i]%mod;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int V,m,mx=0;cin>>V>>m,inv2=qpow(2,mod-2);
    for(int i=1;i<=m;i++){
        int x=sg(i);
        t[x]++,mx=max(mx,x);
    }
    n=1;
    while(n<=mx)n<<=1;
    FWT(t,1);
    b[0]=1,FWT(b,1);
    while(V){
        if(V&1)mul(b,t);
        mul(t,t),V>>=1;
    }
    FWT(b,-1);
    int ans=0;
    for(int i=1;i<n;i++)
        (ans+=b[i])%=mod;
    cout<<ans;
}