#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,B=3000,K=1e5;
int n,m,a[N];
int bk,pos[N];
int Ans[N];
struct node{
    int l,r,x,id,t;
}qu[N];
int tot,cnt[N];
bitset<N>bt1,bt2;
void add(int x){
    if(!cnt[x])
        bt1[x]=1,bt2[K-x]=1;
    cnt[x]++;
}
void del(int x){
    if(!--cnt[x])
        bt1[x]=0,bt2[K-x]=0;
}
int getmul(int x){
    for(int i=1;i*i<=x;i++)
        if(x%i==0&&bt1[i]&&bt1[x/i])
            return 1;
    return 0;
}
int getdiv(int x){
    for(int i=1;i*x<=K;i++)
        if(bt1[i]&&bt1[i*x])return 1;
    return 0;
}
void mo(){
    sort(qu+1,qu+tot+1,[](node A,node B){
        return pos[A.l]^pos[B.l]?A.l<B.l:(pos[A.l]&1)?A.r<B.r:A.r>B.r;
    });
    int l=1,r=0;
    for(int i=1;i<=tot;i++){
        while(r<qu[i].r)add(a[++r]);
        while(r>qu[i].r)del(a[r--]);
        while(l>qu[i].l)add(a[--l]);
        while(l<qu[i].l)del(a[l++]);
        if(qu[i].t==1)
            Ans[qu[i].id]=((bt1<<qu[i].x)&bt1).any();
        else if(qu[i].t==2)
            Ans[qu[i].id]=((bt1<<(K-qu[i].x))&bt2).any();
        else if(qu[i].t==3)
            Ans[qu[i].id]=getmul(qu[i].x);
        else Ans[qu[i].id]=getdiv(qu[i].x);
    }
}
vector<int>ql[N],qr[N],qi[N];
int pre[N],maxl[N];
void solve(){
    for(int x=1;x<=B;x++){
        if(ql[x].empty())
            continue;
        int l=0;
        for(int i=1;i<=n;i++){
            int y=a[i];pre[y]=i;
            if(x*y<=K)
                l=max(l,pre[x*y]);
            if(y%x==0)l=max(l,pre[y/x]);
            maxl[i]=l;
        }
        for(int i=0;i<ql[x].size();i++)
            Ans[qi[x][i]]=(ql[x][i]<=maxl[qr[x][i]]);
        memset(pre,0,sizeof(pre));
        memset(maxl,0,sizeof(maxl));
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    bk=n/sqrt(m);
    for(int i=1;i<=n;i++)
        pos[i]=i/bk+1;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        int op,l,r,x;cin>>op>>l>>r>>x;
        if(op==4&&x<=B)
            ql[x].push_back(l),qr[x].push_back(r),qi[x].push_back(i);
        else qu[++tot]={l,r,x,i,op};
    }
    mo();
    solve();
    for(int i=1;i<=m;i++)
        puts(Ans[i]?"yuno":"yumi");
}