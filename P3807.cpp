#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,p;
int jc[N],inv[N];
int qpow(int x,int y,int s=1){
    while(y){
        if(y&1)s*=x,s%=p;
        x*=x,x%=p,y>>=1;
    }
    return s;
}
int C(int n,int m){
    if(n<m)return 0;
    if(n<p&&m<p)
        return jc[n]*inv[m]%p*inv[n-m]%p;
    return C(n/p,m/p)*C(n%p,m%p)%p;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n>>m>>p,n+=m,jc[0]=1;
        for(int i=1;i<=p-1;i++)jc[i]=jc[i-1]*i%p;
        inv[p-1]=qpow(jc[p-1],p-2);
        for(int i=p-1;i>=1;i--)inv[i-1]=inv[i]*i%p;
        cout<<C(n,m)<<"\n";
    }
}