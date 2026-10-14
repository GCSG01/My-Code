#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
vector<int>g[N];
int n;
int deg[N],l[N],r[N],tot,p[N];
priority_queue<int>q;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>l[i]>>r[i],g[i].clear(),deg[i]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(i!=j&&l[i]<l[j]&&r[j]<r[i])
                    g[i].push_back(j),deg[j]++;
        for(int i=1;i<=n;i++)
            if(!deg[i])q.push(i);
        tot=0;
        while(!q.empty()){
            int u=q.top();q.pop();p[u]=++tot;
            for(int v:g[u])
                if(!--deg[v])
                    q.push(v);
        }
        for(int i=1;i<=n;i++)cout<<n-p[i]+1<<" ";
        cout<<"\n";
    }
}