#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,g[N],sum[N];
int f[N],q[N],mx[N];
multiset<int>st;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>g[i],sum[i]=sum[i-1]+g[i];
    for(int i=1;i<=n;i++)
        if(g[i]>m)
            return cout<<-1,0;
    int l=1,r=0;
    for(int i=1;i<=n;i++){
        while(l<=r&&sum[i]-sum[q[l]]>m)l++,st.erase(f[q[l-1]]+g[q[l]]);
        while(l<=r&&g[q[r]]<g[i])r--,st.erase(f[q[r]]+g[q[r+1]]);
        if(l<=r)st.insert(f[q[r]]+g[i]);
        q[++r]=i;
        int L=0,R=i-1,ans=-1;
        while(L<=R){
            int mid=(L+R)>>1;
            if(sum[i]-sum[mid]>m)
                L=mid+1;
            else ans=mid,R=mid-1;
        }
        f[i]=f[ans]+g[q[l]];
        if(st.size())
            f[i]=min(f[i],*st.begin());
    }
    cout<<f[n];
}