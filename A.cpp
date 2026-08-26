#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n;
vector<int>pos[N];
int mx[N<<2],tag[N<<2];
bool pr[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
inline void upd(int l,int r,int p,int v){
    return mx[p]=v,pr[p]=((r-l+1)&1)&((n+1-v)&1),tag[p]=v,void();
}
inline void push_down(int l,int r,int p){
    if(tag[p]==-1||l==r)return ;
    upd(l,mid,ls,tag[p]),upd(mid+1,r,rs,tag[p]),tag[p]=-1;
}
inline void push_up(int p){
    mx[p]=max(mx[ls],mx[rs]),pr[p]=pr[ls]^pr[rs];
}
void build(int l,int r,int p){
    tag[p]=-1;
    if(l==r)
        return mx[p]=l,pr[p]=(n+1-l)&1,void();
    build(l,mid,ls),build(mid+1,r,rs),push_up(p);
}
int query(int l,int r,int p,int s,int t,int c){
    if(t<l||r<s||mx[p]<c)return n+1;
    if(l==r)return l;
    push_down(l,r,p);
    int sum=query(l,mid,ls,s,t,c);
    if(sum!=n+1)return sum;
    return query(mid+1,r,rs,s,t,c);
}
void update(int l,int r,int p,int s,int t,int v){
    if(t<l||r<s)return ;
    if(s<=l&&r<=t)
        return upd(l,r,p,v);
    push_down(l,r,p);
    update(l,mid,ls,s,t,v),update(mid+1,r,rs,s,t,v),push_up(p);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1,x;i<=n;i++)
        cin>>x,pos[x].push_back(i);
    build(1,n,1);
    int pre=pr[1],ans=0;
    for(int i=0;i<=n;i++){
        int lst=0;
        for(int p:pos[i])
            update(1,n,1,lst+1,min(query(1,n,1,lst+1,p,p)-1,p),p),lst=p;
        update(1,n,1,lst+1,min(query(1,n,1,lst+1,n,n+1)-1,n),n+1);
        if(pre^pr[1])ans^=i;
        pre=pr[1];
    }
    cout<<ans;
    return 0;
}