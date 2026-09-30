#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,s,k,mid,Ans;
struct node{
    int u,v,w,c;
}e[N];
int fa[N];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int check(){
    for(int i=1;i<=m;i++)
        if(!e[i].c)e[i].w+=mid;
    for(int i=1;i<=n;i++)fa[i]=i;
    sort(e+1,e+m+1,[](node A,node B){return A.w!=B.w?A.w<B.w:A.c<B.c;});
    int sum=0;Ans=0;
    for(int i=1;i<=m;i++){
        auto [u,v,w,c]=e[i];
        u=find(u),v=find(v);
        if(u==v)continue;
        fa[u]=v,Ans+=w,sum+=!c;
    }
    for(int i=1;i<=m;i++)
        if(!e[i].c)e[i].w-=mid;
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie();
    cin>>n>>m>>s>>k;
    int cnt=n;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w,e[i].c=(e[i].u!=s&&e[i].v!=s);
        if(find(e[i].u)!=find(e[i].v))
            fa[find(e[i].u)]=find(e[i].v),cnt--;
    }
    if(cnt!=1)return cout<<"Impossible",0;
    mid=1e9;
    if(check()>k)return cout<<"Impossible",0;
    mid=-1e9;
    if(check()<k)return cout<<"Impossible",0;
    int l=-4e4,r=4e4,ans=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(check()>=k)l=mid+1,ans=Ans-mid*k;
        else r=mid-1;
    }
    cout<<ans;
}