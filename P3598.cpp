#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
const int mod=1e9+7;
int n,x;
gp_hash_table<int,int>t1,t2;
int qpow(int x,int y,int s=1){
    int flag=0;
    if(y<0)flag=1,y=-y;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    if(flag)s=qpow(s,mod-2);
    return s;
}
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
    cin>>x>>n,x%=mod;
    for(int i=1,a;i<=n;i++){
        cin>>a,a++,t2=t1;
        for(auto [x,y]:t2)
            t1[gcd(a,x)]-=y;
        t1[a]++;
    }
    int ans=1;
    for(auto [a,b]:t1)
        ans=ans*qpow(qpow(x,a)-1,b)%mod;
    cout<<ans*qpow(x-1,mod-2)%mod;
}