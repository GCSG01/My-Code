#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
int n,m,K;
struct node{
    int v,id;
};
vector<node>e[N];
int in[N],flag[N],ans[N];
void topo(){
    queue<int>q;
    for(int i=1;i<=n;i++)
        if(in[i]<2)flag[i]=0,q.push(i);
    while(!q.empty()){
        int x=q.front();q.pop();
        for(auto y:e[x]){
            in[y.v]--;
            if(in[y.v]<2&&flag[y.v])q.push(y.v),flag[y.v]=0;
        }
    }
}
void dfs(int x,int fa){
    if(flag[x])return ;
    for(auto y:e[x])
        if(y.v!=fa){
            if(y.id>m)ans[y.id-m]=1;
            dfs(y.v,x);
        }
}
int bok[N];
// int bok[]={0,0,1,1,1,0,1};
int AAns=0;
struct edge{
    int u,v;
}ed[N];
int val[N],vv[N];
bool check(){
    for(int i=1;i<=n;i++)e[i].clear();
    for(int i=1;i<=m;i++)
        if(bok[i]==0)
            e[ed[i].u].push_back({ed[i].v,0});
        else e[ed[i].v].push_back({ed[i].u,0});
    val[K]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)vv[j]=0;
        for(int j=1;j<=n;j++){
            bool flg=0;
            for(auto v:e[j])
                if(val[v.v]==1){
                    flg=1;
                    break;
                }
            vv[j]=flg;
        }
        for(int j=1;j<=n;j++)val[j]=vv[j];
    }
    int sum=0;
    for(int i=1;i<=n;i++)sum+=val[i];
    return sum==1;
}
void sol(int x){
    if(AAns)return ;
    if(x>m){
        if(check()){
            AAns=1;
            for(int i=1;i<=m;i++)
                ans[i]=bok[i];
            }
        return ;
    }
    bok[x]=0;
    sol(x+1);
    bok[x]=1;
    sol(x+1);
    return ;
}
void baoli(){
    AAns=0;
    for(int i=1;i<=n;i++)e[i].clear(),val[i]=0;
    sol(1);
    if(!AAns)return cout<<"No\n",void();
    cout<<"Yes\n";
    for(int i=1;i<=m;i++)
        cout<<ans[i];
    cout<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    while(t--){
        cin>>n>>m>>K;
        for(int i=1;i<=n;i++)e[i].clear(),flag[i]=1,ans[i]=0,in[i]=0;
        for(int i=1;i<=m;i++){
            int u,v;cin>>u>>v,ed[i]={u,v};
            e[u].push_back({v,i}),e[v].push_back({u,m+i}),in[u]++,in[v]++;
        }
        if(n<=15&&m<=15){
            baoli();
            continue;
        }
        if(m==n-1){
            cout<<"No\n";
            continue;
        }
        topo();
        dfs(K,0);
        int pos=0;
        for(int i=1;i<=n;i++)
            if(flag[i]){
                pos=i;break;
            }
        if(pos==0){
            cout<<"No\n";
            continue;
        }
        for(int i=1;i<=n;i++)
            if(flag[i]){
                for(auto y:e[i])
                    if(!flag[y.v]){
                        if(y.id>m)ans[y.id-m]=0;
                        else ans[y.id]=1;
                    }
            }
        vector<int>b;
        int cur=pos,pre=0;
        while(1){
            b.push_back(cur);
            int nxt=0;
            for(auto y:e[cur])
                if(flag[y.v]&&y.v!=pre){
                    nxt=y.v;
                    break;
                }
            if(nxt==0||nxt==pos)break;
            pre=cur,cur=nxt;
        }
        for(int i=0;i<b.size();i++){
            int u=b[i],v=b[(i+1)%b.size()];
            for(auto y:e[u])
                if(y.v==v){
                    if(y.id>m)ans[y.id-m]=1;
                    else ans[y.id]=0;
                }
        }
        cout<<"Yes\n";
        for(int i=1;i<=m;i++)
            cout<<(ans[i]^1);
        cout<<"\n";
    }
    return 0;
}