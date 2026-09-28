#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5,LG=30;
int n,m,res[LG+1],tr[N<<2][LG+1];
inline void insert(int *p,int x){
    for(int i=LG;i>=0;i--){
        if(!(x>>i&1))continue;
        if(!p[i])
            return p[i]=x,void();
        x^=p[i];
    }
}
void update(int p,int l,int r,int x,int v){
    insert(tr[p],v);
    if(l==r)return;
    int mid=(l+r)>>1;
    if(x<=mid)update(p<<1,l,mid,x,v);
    else update(p<<1|1,mid+1,r,x,v);
}
void merge(int *p,int *q){
    for(int i=LG;i>=0;i--)
        if(q[i])
            insert(p,q[i]);
}
void query(int p,int l,int r,int x,int y){
    if(x<=l&&r<=y)
        return merge(res,tr[p]);
    int mid=(l+r)>>1;
    if(x<=mid)query(p<<1,l,mid,x,y);
    if(y>mid)query(p<<1|1,mid+1,r,x,y);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    while(n--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1)
            update(1,1,m,l,r);
        else{
            memset(res,0,sizeof(res));
            query(1,1,m,l,r);
            int ans=0;
            for(int i=LG;i>=0;i--)
                ans=max(ans,ans^res[i]);
            cout<<ans<<"\n";
        }
    }
}