#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int n,L,R,ans=-1e18;
int g[N],f[N],tr[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
int query(int l,int r,int p,int ql,int qr){
    if(ql<=l&&r<=qr)return tr[p];
    int mx=-1e18;
    if(ql<=mid)mx=max(mx,query(l,mid,ls,ql,qr));
    if(qr>mid)mx=max(mx,query(mid+1,r,rs,ql,qr));
    return mx;
}
void update(int l,int r,int p,int x,int k){
    if(l==r)
        return tr[p]=max(tr[p],k),void();
    if(x<=mid)update(l,mid,ls,x,k);
    if(x>mid)update(mid+1,r,rs,x,k);
    tr[p]=max(tr[ls],tr[rs]);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    memset(f,-0x3f,sizeof f);
    memset(tr,-0x3f,sizeof tr);
    cin>>n>>L>>R,update(1,n*2,1,1,0);
    for(int i=0;i<=n;i++)cin>>g[i];
    for(int i=L;i<=n+R;i++){
        f[i]=g[i]+query(1,n*2,1,max(1ll,i-R+1),max(1ll,i-L+1)),update(1,n*2,1,i+1,f[i]);
        if(i>=n)ans=max(ans,f[i]);
    }
    cout<<ans;
}