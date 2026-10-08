#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,k,g[N],sum[N];
int q[N],l,rt;
int f0[N],f1[N],v[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>sum[i],sum[i]+=sum[i-1];
    q[l=rt=1]=0;
    for(int i=1;i<=n;i++){
        f0[i]=max(f0[i-1],f1[i-1]),v[i]=f0[i]-sum[i];
        while(l<=rt&&q[l]<i-k)l++;
        f1[i]=v[q[l]]+sum[i];
        while(l<=rt&&v[q[rt]]<v[i])rt--;
        q[++rt]=i;
        // cout<<f0[i]<<" "<<f1[i]<<' '<<v[i]<<"\n";
    }
    cout<<max(f0[n],f1[n]);
}