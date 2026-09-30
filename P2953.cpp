#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int f[N];
inline int mn(int x){
    int s=10;
    while(x)s=min(s,x%10==0?10:x%10),x/=10;
    return s;
}
inline int mx(int x){
    int s=0;
    while(x)s=max(s,x%10),x/=10;
    return s;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    for(int i=0;i<=9;i++)f[i]=1;
    for(int i=10;i<=N-5;i++)
        f[i]=(f[i-mn(i)]&f[i-mx(i)])^1;
    int q;cin>>q;
    while(q--){
        int x;cin>>x;
        cout<<(f[x]?"YES\n":"NO\n");
    }
}