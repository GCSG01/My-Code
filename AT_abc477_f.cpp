#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+5;
ll t[3][N];
int l[N],r[N];
int pos[N];
ll Ans[N];
int n,m,q;
struct node{
    int a,b,c,d,id;
}qu[N];
inline int lowbit(int x){return x&-x;}
void add(int op,int x,int v){
    while(x<=m)t[op][x]+=v,x+=lowbit(x);
}
ll get(int op,int x,int s=0){
    while(x)s+=t[op][x],x-=lowbit(x);
    return s;
}
inline void update(int l,int r,int x){
    add(1,l,x),add(2,l,-(l-1)*x),add(1,r+1,-x),add(2,r+1,r*x);
}
inline ll query(int l,int r){
    l--;
    return r*get(1,r)+get(2,r)-l*get(1,l)-get(2,l);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int bk;cin>>n>>m>>q,bk=sqrt(n);
    for(int i=1;i<=n;i++)cin>>l[i]>>r[i],pos[i]=i/bk+1;
    for(int i=1;i<=q;i++)cin>>qu[i].a>>qu[i].b>>qu[i].c>>qu[i].d,qu[i].id=i;
    sort(qu+1,qu+q+1,[](node A,node B){
        return pos[A.a]==pos[B.a]?(pos[A.a]&1?A.b<B.b:A.b>B.b):A.a<B.a;
    });
    int L=1,R=0;
    for(int i=1;i<=q;i++){
        while(L>qu[i].a)L--,update(l[L],r[L],1);
        while(R<qu[i].b)R++,update(l[R],r[R],1);
        while(L<qu[i].a)update(l[L],r[L],-1),L++;
        while(R>qu[i].b)update(l[R],r[R],-1),R--;
        Ans[qu[i].id]=query(qu[i].c,qu[i].d);
    }
    for(int i=1;i<=q;i++)cout<<Ans[i]<<"\n";
}