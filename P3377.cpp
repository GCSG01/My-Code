#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
int dep[N];
int rt[N];
int vis[N];
struct node{
    int id,v,l,r;
    bool operator<(node x)const{
        return v==x.v?id<x.id:v<x.v;
    }
}tr[N];
int find(int x){
    return rt[x]==x?x:rt[x]=find(rt[x]);
}
#define ls(A) tr[(A)].l
#define rs(A) tr[(A)].r
int merge(int x,int y){
    if(!x||!y)
        return x+y;
    if(tr[y]<tr[x])
        swap(x,y);
    rs(x)=merge(rs(x),y);
    if(dep[ls(x)]<dep[rs(x)])
        swap(ls(x),rs(x));
    dep[x]=dep[rs(x)]+1;
    return x;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m,dep[0]=-1;
    for(int i=1;i<=n;i++)
        cin>>tr[i].v,rt[i]=i,tr[i].id=i;
    while(m--){
        int op,x,y;cin>>op>>x;
        if(op==1){
            cin>>y;
            if(vis[x]||vis[y])continue;
            x=find(x),y=find(y);
            if(x!=y)
                rt[x]=rt[y]=merge(x,y);
        }
        else{
            if(vis[x]){
                cout<<"-1\n";
                continue;
            }
            x=find(x);
            vis[x]=1;
            rt[ls(x)]=rt[rs(x)]=rt[x]=merge(ls(x),rs(x));
            ls(x)=rs(x)=dep[x]=0;
            cout<<tr[x].v<<"\n";
        }
    }
    return 0;
}