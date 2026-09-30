#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5,mod=666623333;
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
struct node{
    int l,r;
}a[N];
int n,k,m;
int st[N],top;
int L[N],R[N];
int f[N],inv[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k>>m;
    for(int i=1;i<=m;i++)
        cin>>a[i].l>>a[i].r;
    sort(a+1,a+1+m,[](node A,node B){return A.l==B.l?A.r>B.r:A.l<B.l;});
    for(int i=1;i<=m;i++){
        while(top&&a[i].r<=a[st[top]].r)top--;
        st[++top]=i;
    }
    m=top;
    for(int i=1;i<=m;i++)a[i]=a[st[i]];
    int h=1,t=0;
    for(int i=1;i<=n;i++){
        while(t<m&&a[t+1].l<=i)t++;
        while(h<=t&&a[h].r<i)h++;
        L[i]=h,R[i]=t;
    }
    int ans=0;
    for(int x=1;x<=k;x++){
        int sum=1,p=(x-1)*qpow(k,mod-2)%mod,cnt=1;
        inv[0]=1,f[0]=1;
        for(int i=1;i<=n;i++)
            inv[i]=inv[i-1]*qpow(1-p,mod-2)%mod;
        for(int i=1,j=0;i<=n;i++){
            while(j<i&&R[j]<L[i]-1)
                (sum-=f[j]*inv[j]%mod)%=mod,j++;
            f[i]=sum*cnt%mod*p%mod,(cnt*=1-p)%=mod;
            (sum+=f[i]*inv[i]%mod)%=mod;
        }
        cnt=1;
        for(int i=n;i&&R[i]==m;i--,(cnt*=1-p)%=mod)
            (ans-=f[i]*cnt%mod)%=mod;
        ans++;
    }
    if(ans<0)ans+=mod;
    cout<<ans;
}