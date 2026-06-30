#include<bits/stdc++.h>
using namespace std;
void rd(int &x){
    char c=0;int f=1;x=0;
    while(c<'0'||c>'9')
        f=(c=='-'?-1:f),c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
    x=x*f;
}
const int N=3e5+5;
struct node{
    int s[2],siz,fa,key;
    node(){s[0]=s[1]=siz=fa=key=0;}
}tr[N];
#define ls(x) tr[(x)].s[0]
#define rs(x) tr[(x)].s[1]
#define fa(x) tr[(x)].fa
int rt,idx;
inline int nw(int key){
    return tr[++idx].key=key,tr[idx].siz=1,idx;
}
inline void push_up(int x){
    tr[x].siz=tr[ls(x)].siz+tr[rs(x)].siz+1;
}
inline void clear(int x){
    ls(x)=rs(x)=fa(x)=tr[x].siz=tr[x].key=0;
}
inline int get(int x){
    return x==rs(fa(x));
}
void rotate(int x){
    int y=fa(x),z=fa(y),c=get(x);
    if(tr[x].s[c^1])fa(tr[x].s[c^1])=y;
    tr[y].s[c]=tr[x].s[c^1],tr[x].s[c^1]=y,fa(y)=x,fa(x)=z;
    if(z)tr[z].s[y==tr[z].s[1]]=x;
    push_up(y),push_up(x);
    return ;
}
void splay(int x){
    for(int f=fa(x);f=fa(x),f;rotate(x))
        if(fa(f))rotate(get(x)==get(f)?f:x);
    rt=x;
    return ;
}
void ins(int key){
    int now=rt,f=0;
    while(now)f=now,now=tr[now].s[key>tr[now].key];
    now=nw(key),fa(now)=f,tr[f].s[key>tr[f].key]=now,splay(now);
    return ;
}
void del(int key){
    int now=rt,p=0;
    while(now&&tr[now].key!=key)
        p=now,now=tr[now].s[tr[now].key<key];
    if(!now)return splay(p),void();
    splay(now);
    int cur=ls(now);
    if(!cur)
        return rt=rs(now),fa(rs(now))=0,clear(now),void();
    while(rs(cur))cur=rs(cur);
    rs(cur)=rs(now),fa(rs(now))=cur,fa(ls(now))=0,clear(now);
    push_up(cur),splay(cur);
    return ;
}
int pre(int key){
    int now=rt,ans=0,f=0;
    while(now){
        f=now;
        if(tr[now].key>=key)now=ls(now);
        else ans=tr[now].key,now=rs(now);
    }
    return splay(f),ans;
}
int nxt(int key){
    int now=rt,ans=0,f=0;
    while(now){
        f=now;
        if(tr[now].key<=key)now=rs(now);
        else ans=tr[now].key,now=ls(now);
    }
    return splay(f),ans;
}
int rnk(int key){
    int now=rt,ans=1,f=0;
    while(now){
        f=now;
        if(tr[now].key<key)ans+=tr[ls(now)].siz+1,now=rs(now);
        else now=ls(now);
    }
    return splay(f),ans;
}
int kth(int rk){
    int now=rt;
    while(now){
        int sz=tr[ls(now)].siz+1;
        if(sz>rk)now=ls(now);
        else if(sz==rk)break;
        else rk-=sz,now=rs(now);
    }
    return splay(now),tr[now].key;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        int op,x;cin>>op>>x;
        if(op==1)ins(x);
        else if(op==2)del(x);
        else if(op==3)cout<<rnk(x)<<"\n";
        else if(op==4)cout<<kth(x)<<"\n";
        else if(op==5)cout<<pre(x)<<"\n";
        else cout<<nxt(x)<<"\n";
    }
    return 0;
}