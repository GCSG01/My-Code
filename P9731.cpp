#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int N=5e5+5;
int n,s,t;
int a[N],col[N],vis[N],st[N],top;
vector<pair<int,int>>e[N],pos[N];
inline int get(int x,int y){return(x-1)*s+y;}
void dfs(int x,int c){
    top=0,st[++top]=x,vis[x]=1,col[x]=c;
    while(top){
        int u=st[top--];
        for(auto[v,w]:e[u])
            if(!vis[v])
                vis[v]=1,col[v]=col[u]^w,st[++top]=v;
    }
    return ;
}
void solve(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2,len=(r-l+1)/2;
    for(int i=1;i<=n;i++)
        for(int j=0;j<len;j++){
            int idx=get(i,l+j*2);
            e[idx].clear(),vis[idx]=0;
            int u=a[idx],v=a[get(i,l+j*2+1)];
            if(u==v)continue;
            pos[u].push_back({idx,1}),pos[v].push_back({idx,2});
        }
    for(int i=1;i<=t;pos[i++].clear())
        for(int j=0;j+1<pos[i].size();j+=2){
            int u=pos[i][j].fi,pu=pos[i][j].se;
            int v=pos[i][j+1].fi,pv=pos[i][j+1].se;
            int w=(pu==pv)?1:0;
            e[u].push_back({v,w});e[v].push_back({u,w});
        }
    for(int i=1;i<=n;i++)
        for(int j=0;j<len;j++){
            int idx=get(i,l+j*2);
            if(!vis[idx])dfs(idx,0);
        }
    for(int i=1;i<=n;i++){
        vector<int>lv,rv;
        for(int j=0;j<len;j++){
            int idx=get(i,l+j*2);
            if(col[idx]==0)lv.push_back(a[idx]),rv.push_back(a[get(i,l+j*2+1)]);
            else lv.push_back(a[get(i,l+j*2+1)]),rv.push_back(a[idx]);
        }
        for(int j=0;j<len;j++)
            a[get(i,l+j)]=lv[j],a[get(i,mid+1+j)]=rv[j];
    }
    return solve(l,mid),solve(mid+1,r);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>s>>t;
    for(int i=1;i<=n;i++)
        for(int j=0;j<s;j++)
            cin>>a[get(i,j)];
    solve(0,s-1);
    for(int i=1;i<=n;i++,cout<<"\n")
        for(int j=0;j<s;j++)
            cout<<a[get(i,j)]<<" ";
    return 0;
}