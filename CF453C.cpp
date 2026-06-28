#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=5e5+5;
vector<int>e[N];
int x[N],vis[N];
int a[N];
int n,m,ans;
void dfs(int u,int fa){
    vis[u]=1,a[++ans]=u,x[u]^=1;
    for(int v:e[u])
        if(v!=fa&&!vis[v])
            dfs(v,u),a[++ans]=u,x[u]^=1;
    if(x[u])
        a[++ans]=fa,a[++ans]=u,x[u]^=1,x[fa]^=1;
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v),e[v].push_back(u);
    }
    int s=0;
    for(int i=1;i<=n;i++){
        cin>>x[i];
        if(x[i])s=i;
    }
    if(s){
        dfs(s,-1);
        for(int i=1;i<=n;i++)
            if(!vis[i]&&x[i])
                return cout<<-1,0;
    }
    if(ans>1&&a[ans-1]==-1)ans-=3;
    cout<<ans<<"\n";
    for(int i=1;i<=ans;i++)
        cout<<a[i]<<" ";
    return 0;
}