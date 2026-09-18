#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
struct node{
    int siz,val,l,r;
    bool flag;
}tr[N];
int n,rt,tot;
#define ls(x) tr[x].l
#define rs(x) tr[x].r
inline void pushup(int x){
    tr[x].siz=tr[ls(x)].siz+tr[rs(x)].siz+1;
}
inline void pushdown(int x){
    if(!tr[x].flag)return ;
    swap(ls(x),rs(x));
    if(ls(x))tr[ls(x)].flag^=1;
    if(rs(x))tr[rs(x)].flag^=1;
    tr[x].flag=0;
}
inline int merge(int x,int y){
    if(!x||!y)return x+y;
    if(tr[x].val<=tr[y].val)
        return pushdown(x),rs(x)=merge(rs(x),y),pushup(x),x;
    else return pushdown(y),ls(y)=merge(x,ls(y)),pushup(y),y;
}
int st[N],top;
inline void build(int x){
    while(top&&tr[x].val<tr[st[top]].val)
        ls(x)=st[top--],pushup(ls(x));
    if(top)rs(st[top])=x;
    st[++top]=x;
}
inline void update(int x){
    int l=ls(x),r=rs(x);
    ls(x)=rs(x)=0;
    tr[l].flag^=1;
    rt=merge(l,r);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1,x;i<=n;i++)
        cin>>x,tr[i].val=x*n+i,tr[i].siz=1,build(i);
    while(top)pushup(st[top--]);
    rt=st[1];
    for(int i=1;i<=n;i++)
        pushdown(rt),cout<<tr[ls(rt)].siz+i<<" ",update(rt);
    return 0;
}