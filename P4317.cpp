#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=53,mod=1e7+7;
int f[N];
int qpow(int x,int y,int s=1){
    for(;y;x*=x,x%=mod,y>>=1)
        if(y&1)s*=x,s%=mod;
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,cnt=0;cin>>n;
    for(int i=50;~i;i--){
        for(int j=50;j;j--)
            f[j]+=f[j-1];
        if((n>>i)&1)f[cnt]++,cnt++;
    }
    f[cnt]++;
    int ans=1;
	for(int i=1;i<=50;i++)
		ans=ans*qpow(i,f[i])%mod;
	cout<<ans;
}