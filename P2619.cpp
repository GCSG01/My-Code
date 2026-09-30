#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,P,mid,Ans;
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
        fa[u]=v,sum+=!c,Ans+=w;
    }
    for(int i=1;i<=m;i++)
        if(!e[i].c)e[i].w-=mid;
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>P;
    for(int i=1;i<=m;i++)
        cin>>e[i].u>>e[i].v>>e[i].w>>e[i].c,e[i].u++,e[i].v++;
    int l=-200,r=200,ans=-5;;
    while(l<=r){
        mid=(l+r)>>1;
        if(check()>=P)l=mid+1,ans=Ans-mid*P;
        else r=mid-1;
    }
    cout<<ans;
}