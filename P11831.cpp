#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=2e5+5,W=1570,B=320;
using ull=unsigned long long;

struct bitst{
    ull s[W];
    inline void reset(){memset(s,0,sizeof(s));}
    inline void set(int x){s[x>>6]|=1ull<<(x&63);}
    inline void flip(int x){s[x>>6]^=1ull<<(x&63);}
    inline void operator|=(const bitst&o){
        for(int i=0;i<W;i++)s[i]|=o.s[i];
    }
    inline void operator^=(const bitst&o){
        for(int i=0;i<W;i++)s[i]^=o.s[i];
    }
    inline void operator&=(const bitst&o){
        for(int i=0;i<W;i++)s[i]&=o.s[i];
    }
    inline bool val(int x){return s[x>>6]>>(x&63)&1;}
};

bitst to[N],sa[B],sb[B],c;
int n,m,q,head[N],ver[M],nxt[M],ecnt;
int g[N],b[N],ida[N],idb[N];

inline int rd(){
    int x=0;
    char c=getchar_unlocked();
    while(c<'0'||c>'9')c=getchar_unlocked();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar_unlocked();
    return x;
}
inline int L(int x){return x*B;}
inline int R(int x){return min(n,x*B+B-1);}
inline void add(int u,int v){
    ver[++ecnt]=v,nxt[ecnt]=head[u],head[u]=ecnt;
}

void solve(){
    n=rd(),m=rd(),q=rd(),ecnt=0;
    int k=n/B;
    for(int i=1;i<=n;i++)to[i].reset(),to[i].set(i),head[i]=0;
    for(int i=1,u,v;i<=m;i++)u=rd(),v=rd(),add(u,v);
    for(int i=1;i<=n;i++)g[i]=rd(),ida[g[i]]=i;
    for(int i=1;i<=n;i++)b[i]=rd(),idb[b[i]]=i;
    for(int i=n;i;i--)
        for(int e=head[i];e;e=nxt[e]){
            int v=ver[e];
            for(int j=v>>6;j<W;j++)to[i].s[j]|=to[v].s[j];
        }
    for(int i=0;i<=k+1;i++)sa[i].reset(),sb[i].reset();
    for(int i=1;i<=n;i++)sa[g[i]/B].set(i),sb[b[i]/B].set(i);
    for(int i=k-1;i>=0;i--)sa[i]|=sa[i+1],sb[i]|=sb[i+1];
    while(q--){
        int op=rd(),x=rd(),y=rd(),r;
        if(op==1){
            int u=g[x],v=g[y],p=u/B,q=v/B;
            if(p<q)for(int i=p+1;i<=q;i++)sa[i].flip(x),sa[i].flip(y);
            else for(int i=q+1;i<=p;i++)sa[i].flip(x),sa[i].flip(y);
            swap(ida[u],ida[v]),swap(g[x],g[y]);
        }else if(op==2){
            int u=b[x],v=b[y],p=u/B,q=v/B;
            if(p<q)for(int i=p+1;i<=q;i++)sb[i].flip(x),sb[i].flip(y);
            else for(int i=q+1;i<=p;i++)sb[i].flip(x),sb[i].flip(y);
            swap(idb[u],idb[v]),swap(b[x],b[y]);
        }else{
            r=rd();
            int bl=y/B,br=r/B;
            c=sa[bl];
            if(br<k)c^=sa[br+1];
            for(int i=bl*B;i<y;i++)if(i)c.flip(ida[i]);
            for(int i=R(br);i>r;i--)c.flip(ida[i]);
            c&=to[x];
            int pos=-1;
            for(int i=0;i<W;i++)
                while(pos+1<B&&(c.s[i]&sb[pos+1].s[i]))++pos;
            if(pos<0){
                puts("0");
                continue;
            }
            for(int j=R(pos);j>=L(pos);j--)
                if(c.val(idb[j])){
                    printf("%d\n",j);
                    break;
                }
        }
    }
}

int main(){
    int C=rd(),T=rd();
    while(T--)solve();
}