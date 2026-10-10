#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=1e9+7;
int qpow(int x,int y,int s=1){
    for(;y;x*=x,x%=mod,y>>=1)
        if(y&1)s*=x,s%=mod;
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int w,n,k;cin>>w>>n>>k;
    cout<<w*qpow(qpow(2,k),mod-2)%mod;
}