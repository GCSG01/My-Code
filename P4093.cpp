#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
int a[N],f[N];
int Mn[N],Mx[N];
int id[N];
int tr[N];
inline int lowbit(int x){return x&-x;}
void ins(int x,int y){
    while(x<=N-5)tr[x]=max(tr[x],y),x+=lowbit(x);
}
int query(int x,int s=0){
    while(x)s=max(s,tr[x]),x-=lowbit(x);
    return s;
}
void cdq(int l,int r){
    if(l==r)return f[l]=max(f[l],1ll),void();
    int mid=(l+r)>>1;
    cdq(l,mid);
    for(int i=l;i<=r;i++)id[i]=i;
    sort(id+l,id+mid+1,[](int A,int B){return Mx[A]<Mx[B];});
    sort(id+mid+1,id+r+1,[](int A,int B){return a[A]<a[B];});
    int j=l;
    for(int i=mid+1;i<=r;i++){
        while(j<=mid&&Mx[id[j]]<=a[id[i]])
            ins(a[id[j]],f[id[j]]),j++;
        f[id[i]]=max(f[id[i]],query(Mn[id[i]])+1);
    }
    for(int i=l;i<=mid;i++){
        int x=a[id[i]];
        while(x<=N-5)tr[x]=0,x+=lowbit(x);
    }
    return cdq(mid+1,r);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i],Mn[i]=Mx[i]=a[i];
    for(int i=1,x,y;i<=m;i++)
        cin>>x>>y,Mn[x]=min(Mn[x],y),Mx[x]=max(Mx[x],y);
    cdq(1,n);
    int ans=0;
    for(int i=1;i<=n;i++)ans=max(ans,f[i]);
    cout<<ans;
    return 0;
}