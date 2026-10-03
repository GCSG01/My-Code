#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=-1e18;
int n,a[N],b[N];
int v[N],w[N],pre[N],l[N],r[N];
int mx[N<<2],tag[N<<2];
int sv[2][N];
int sp[2][N],top[2];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void upd(int p,int x){
    mx[p]+=x,tag[p]+=x;
}
inline void push(int p){
    if(!tag[p])return;
    upd(ls,tag[p]),upd(rs,tag[p]),tag[p]=0;
}
void update(int p,int l,int r,int x,int v){
    if(l==r)
        return mx[p]=v,tag[p]=0,void();
    push(p);
    if(x<=mid)update(ls,l,mid,x,v);
    else update(rs,mid+1,r,x,v);
    mx[p]=max(mx[ls],mx[rs]);
}
void add(int p,int l,int r,int s,int t,int v){
    if(s<=l&&r<=t)
        return upd(p,v);
    push(p);
    if(s<=mid)add(ls,l,mid,s,t,v);
    if(t>mid)add(rs,mid+1,r,s,t,v);
    mx[p]=max(mx[ls],mx[rs]);
}
int query(int p,int l,int r,int s,int t){
    if(s<=l&&r<=t)return mx[p];
    int sum=inf;push(p);
    if(s<=mid)sum=max(sum,query(ls,l,mid,s,t));
    if(t>mid)sum=max(sum,query(rs,mid+1,r,s,t));
    return sum;
}
int solve(int n,int *a,int *b,int *v,int *w){
    for(int i=1;i<=n;i++)
        pre[i]=pre[i-1]+v[i];
    fill(l,l+n+1,0);
    fill(r,r+n+1,0);
    int m=4*n+5;
    fill(mx,mx+m,inf);
    fill(tag,tag+m,0);
    top[0]=top[1]=0;
    int k=1;
    while(pre[k]*2<pre[n])k++;
    for(int i=1;i<k;i++)
        l[a[i]]=pre[i];
    for(int i=n;i>k;i--)
        r[a[i]]=pre[n]-pre[i-1];
    int ans=pre[n],sum=0,cnt=0;
    for(int i=1;i<=n;i++){
        int x[2]={l[b[i]],r[b[i]]};
        update(1,1,n,i,pre[n]-sum-x[0]-x[1]);
        for(int j=0;j<2;j++){
            while(top[j]&&sv[j][top[j]]<=x[j]){
                int old=sv[j][top[j]];
                int rr=sp[j][top[j]--];
                int ll=sp[j][top[j]]+1;
                add(1,1,n,ll,rr,old-x[j]);
            }
            sv[j][++top[j]]=x[j],sp[j][top[j]]=i;
        }
        sum+=w[i];
        if(b[i]==a[k])cnt=i;
        ans=max(ans,query(1,1,n,cnt+1,i)+sum);
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)cin>>b[i];
        for(int i=1;i<=n;i++)cin>>v[i];
        for(int i=1;i<=n;i++)cin>>w[i];
        cout<<max(solve(n,b,a,w,v),solve(n,a,b,v,w))<<"\n";
    }
}