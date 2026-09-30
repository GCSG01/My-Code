#include<bits/stdc++.h>
using namespace std;
const int N=3e7+5,inf=INT_MAX;
int siz[N],ls[N],rs[N],val[N],pri[N],root[N];
int cnt,n;
void update(int x,int y){
    siz[x]=siz[y],val[x]=val[y];
    pri[x]=pri[y],ls[x]=ls[y],rs[x]=rs[y];
}
void up(int x){
    if(!x)return ;
    siz[x]=siz[ls[x]]+siz[rs[x]]+1;
}
void split(int rt,int k,int &x,int &y){
    if(!rt)
        return x=y=0,void();
    int nw=++cnt;
    update(nw,rt);
    if(k<val[rt])
        y=nw,split(ls[rt],k,x,ls[y]),up(y);
    else x=nw,split(rs[rt],k,rs[x],y),up(x);
}
int merge(int x,int y){
    if(!x||!y)return x+y;
    int nw=++cnt;
    if(pri[x]<pri[y])
        update(nw,x),rs[nw]=merge(rs[nw],y);
    else update(nw,y),ls[nw]=merge(x,ls[nw]);
    return up(nw),nw;
}
int rk(int x,int v){
    if(!x)return 0;
    if(v<val[x])return rk(ls[x],v);
    return rk(rs[x],v)+siz[ls[x]]+1;
}
void insert(int &x,int v){
    int nw=++cnt;
    val[nw]=v,pri[nw]=rand(),siz[nw]=1,ls[nw]=rs[nw]=0;
    if(!x)return x=nw,void();
    int xx,yy;
    split(x,v,xx,yy);
    x=merge(merge(xx,nw),yy);
}
void erase(int &rt,int v){
    int x,y,z;
    split(rt,v,x,z);
    split(x,v-1,x,y);
    if(y)rt=merge(x,merge(merge(ls[y],rs[y]),z));
    else rt=merge(x,z);
}
int kth(int x,int k){
    if(k<=siz[ls[x]])return kth(ls[x],k);
    if(k==siz[ls[x]]+1)return val[x];
    return kth(rs[x],k-siz[ls[x]]-1);
}
int pre(int x,int k){
    if(!x)return -inf;
    if(val[x]<k)return max(val[x],pre(rs[x],k));
    return pre(ls[x],k);
}
int nxt(int x,int k){
    if(!x)return inf;
    if(val[x]>k)return min(val[x],nxt(ls[x],k));
    return nxt(rs[x],k);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0); 
    cin>>n,root[0]=0;
    for(int i=1;i<=n;i++){
        int v,op,x;cin>>v>>op>>x;
        root[i]=root[v];
        if(op==1)insert(root[i],x);
        if(op==2)erase(root[i],x);
        if(op==3)cout<<rk(root[i],x-1)+1<<"\n";
        if(op==4)cout<<kth(root[i],x)<<"\n";
        if(op==5)cout<<pre(root[i],x)<<"\n";
        if(op==6)cout<<nxt(root[i],x)<<"\n"; 
    }
}