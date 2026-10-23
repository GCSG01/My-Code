#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,cnt=1;
int x[N<<1];
struct line{
    int l,r,h,f;
    bool operator<(const line& b)const{
        return h<b.h;
    }
}line[N<<1];
struct node{
    int l,r,sum,len;
}tr[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
void build(int p,int l,int r){
	tr[p]={l,r,0,0};
    if(l==r)return;
    build(ls,l,mid),build(rs,mid+1,r);
}
void push_up(int p){
    int l=tr[p].l,r=tr[p].r;
    if(tr[p].sum)tr[p].len=x[r+1]-x[l];
    else tr[p].len=tr[ls].len+tr[rs].len;
}
void update(int p,int l,int r,int v){
    int ll=tr[p].l,rr=tr[p].r;
    if(x[rr+1]<=l||r<=x[ll])return ;
    if(l<=x[ll]&&x[rr+1]<=r)
        return tr[p].sum+=v,push_up(p),void();
    update(ls,l,r,v),update(rs,l,r,v),push_up(p);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1,x1,x2,y1,y2;i<=n;i++)
        cin>>x1>>y1>>x2>>y2,x[2*i-1]=x1,x[2*i]=x2,line[2*i-1]={x1,x2,y1,1},line[2*i]={x1,x2,y2,-1};
    n*=2;
    sort(line+1,line+n+1),sort(x+1,x+n+1);
    int tot=unique(x+1,x+n+1)-x-1;
    build(1,1,tot-1);
    int ans=0;
    for(int i=1;i<n;i++)
        update(1,line[i].l,line[i].r,line[i].f),ans+=tr[1].len*(line[i+1].h-line[i].h);
    cout<<ans;
}