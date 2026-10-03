#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=998244353;
int q[N],st[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>q[i];
    if(q[1]!=1)
        return cout<<0,0;
    int top=0,ans=1;
    st[0]=1;
    for(int i=1;i<=n;i++){
        while(top&&q[st[top]]<q[i])top--;
        if(i>1)ans=ans*(i-st[top])%mod;
        st[++top]=i;
    }
    cout<<ans;
}