#include<bits/stdc++.h>
#define int long long
#define pr pair<int,int>
#define fi first
#define se second
using namespace std;
const int mod=19990721,N=1e6+5;
struct mat{
    int a,b,c,d;
};
int ls[N],rs[N],rt,tot;
unsigned key[N];
int len[N],sz[N];
mat sum[N];
bool bit[N],tag[N];
uint64_t bas=123456789123456789ULL;
unsigned rng(){
    uint64_t z=(bas+=0x9e3779b97f4a7c15ULL);
    return z=(z^(z>>30))*0xbf58476d1ce4e5b9ULL,
    z=(z^(z>>27))*0x94d049bb133111ebULL,(unsigned)(z^(z>>31));
}
mat mk(bool b,int l){
    return b?mat{1,0,l,1}:mat{1,l,0,1};
}
mat mul(const mat&x,const mat&y){
    return mat{(x.a*y.a+x.b*y.c)%mod,(x.a*y.b+x.b*y.d)%mod,
        (x.c*y.a+x.d*y.c)%mod,(x.c*y.b+x.d*y.d)%mod};
}
mat get(int x){
    return x?sum[x]:(mat){1,0,0,1};
}
int nw(bool b,int l){
    return tot++,ls[tot]=rs[tot]=0,key[tot]=rng(),
    len[tot]=sz[tot]=l,bit[tot]=b,tag[tot]=0,sum[tot]=mk(b,l),tot;
}
void push_down(int x){
    sz[x]=len[x]+sz[ls[x]]+sz[rs[x]],sum[x]=mul(mul(get(ls[x]),mk(bit[x],len[x])),get(rs[x]));
}
void update(int x){
    if(!x)return ;
    bit[x]=!bit[x],tag[x]=!tag[x];
    sum[x]={sum[x].d,sum[x].c,sum[x].b,sum[x].a};
}
void push(int x){
    if(!x||!tag[x])return ;
    update(ls[x]),update(rs[x]),tag[x]=0;
}
int merge(int x,int y){
    if(!x)return y;
    if(!y)return x;
    if(key[x]>key[y])
        return push(x),rs[x]=merge(rs[x],y),push_down(x),x;
    return push(y),ls[y]=merge(x,ls[y]),push_down(y),y;
}
pr split(int x,int k){
    if(!x)return pr(0,0);
    if(k<=0)return pr(0,x);
    if(k>=sz[x])return pr(x,0);
    push(x);
    int siz=sz[ls[x]];
    if(k<siz){
        pr p=split(ls[x],k);
        return ls[x]=p.se,push_down(x),pr(p.fi,x);
    }
    if(k>siz+len[x]){
        pr p=split(rs[x],k-siz-len[x]);
        return rs[x]=p.fi,push_down(x),pr(x,p.se);
    }
    if(k==siz){
        int xx=ls[x];
        return ls[x]=0,push_down(x),pr(xx,x);
    }
    if(k==siz+len[x]){
        int xx=rs[x];
        return rs[x]=0,push_down(x),pr(x,xx);
    }
    int s=k-siz;
    return pr(
        merge(ls[x],nw(bit[x],s)),
        merge(nw(bit[x],len[x]-s),rs[x])
    );
}
void upgrade(int&rt,int L,int R){
    pr x=split(rt,L-1);
    pr y=split(x.se,R-L+1);
    update(y.fi);
    rt=merge(x.fi,merge(y.fi,y.se));
    return ;
}
mat query(int&rt,int L,int R){
    if(L>R)return {1,0,0,1};
    pr x=split(rt,L-1);
    pr y=split(x.se,R-L+1);
    mat r=get(y.fi);
    return rt=merge(x.fi,merge(y.fi,y.se)),r;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m,lst=0;cin>>n>>m;
    rt=nw(1,n);
    while(m--){
        int op;cin>>op;
        if(op==0){
            int x,y;cin>>x>>y;
            int l=(x+lst)%n+2,r=(y+lst)%n+2;
            if(l>r)swap(l,r);
            upgrade(rt,l,r);
        }
        else{
            int x,y,k;cin>>x>>y>>k;
            int l=(x+lst)%n+1,r=(y+lst)%n+1;
            if(l>r)swap(l,r);
            int ans;
            if(k==0)ans=1;
            else if(k>1)ans=2;
            else if(l==r)ans=2;
            else{
                mat t=query(rt,l+1,r);
                ans=(t.a+t.b+t.c+t.d)%mod;
            }
            cout<<(lst=ans)<<"\n";
        }
    }
    return 0;
}