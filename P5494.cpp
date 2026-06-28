#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int n,m;
int rt[N<<4];
int val[N<<4];
int ch[N<<4][2];
int bac[N<<4],btot,tot,rtot=1;
void del(int p){
    bac[++btot]=p,ch[p][0]=ch[p][1]=val[p]=0;
    return ;
}
int cre(){
    return btot?bac[btot--]:++tot;
}
void modify(int &p,int l,int r,int x,int k){
    if(!p)p=cre();
    val[p]+=k;
    if(l==r)return ;
    int mid=(l+r)>>1;
    if(x<=mid)modify(ch[p][0],l,mid,x,k);
    else modify(ch[p][1],mid+1,r,x,k);

    return ;
}
int query(int p,int l,int r,int ql,int qr){
    if(qr<l||r<ql)return 0;
    if(ql<=l&&r<=qr)return val[p];
    int mid=(l+r)>>1;
    return query(ch[p][0],l,mid,ql,qr)+query(ch[p][1],mid+1,r,ql,qr);
}
int get_rk(int p,int l,int r,int k){
    if(l==r)return l;
    int mid=(l+r)>>1;
    if(k<=val[ch[p][0]])return get_rk(ch[p][0],l,mid,k);
    else return get_rk(ch[p][1],mid+1,r,k-val[ch[p][0]]);
}
int merge(int x,int y){
    if(!x||!y)return x+y;
    val[x]+=val[y];
    ch[x][0]=merge(ch[x][0],ch[y][0]);
    ch[x][1]=merge(ch[x][1],ch[y][1]);
    del(y);
    return x;
}
void split(int x,int &y,int k){
    if(!x)return ;
    y=cre();
    int v=val[ch[x][0]];
    if(k<=v)swap(ch[x][1],ch[y][1]);
    else split(ch[x][1],ch[y][1],k-v);
    if(k<v)split(ch[x][0],ch[y][0],k);
    val[y]=val[x]-k,val[x]=k;
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m);
    for(int i=1,x;i<=n;i++)
        rd(x),modify(rt[1],1,n,i,x);
    while(m--){
        int op,p,x,y;
        rd(op),rd(p);
        if(!op){
            rd(x),rd(y);
            int cnt1=query(rt[p],1,n,1,y),cnt2=query(rt[p],1,n,x,y);
            int tmp=0;
            split(rt[p],rt[++rtot],cnt1-cnt2);
            split(rt[rtot],tmp,cnt2);
            rt[p]=merge(rt[p],tmp);
        }
        else if(op==1)
            rd(x),rt[p]=merge(rt[p],rt[x]);
        else if(op==2){
            rd(x),rd(y);
            modify(rt[p],1,n,y,x);
        }
        else if(op==3){
            rd(x),rd(y);
            cout<<query(rt[p],1,n,x,y)<<"\n";
        }
        else{
            rd(x);
            if(val[rt[p]]<x)cout<<"-1\n";
            else cout<<get_rk(rt[p],1,n,x)<<"\n";
        }
    }
    return 0;
}