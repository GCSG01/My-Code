#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,P,a[N],sum[N];

struct node{
    int v,num;
}f[N];
struct Q{
    int l,r,id;
}q[N];
inline int cost(int l,int r){
    int mid=(l+r)>>1;
    return a[mid]*(mid-l+1)-(sum[mid]-sum[l-1])
        +(sum[r]-sum[mid])-a[mid]*(r-mid);
}
inline node calc(int j,int i){
    return {f[j].v+cost(j+1,i)+m,f[j].num+1};
}
inline bool operator<(node a,node b){
    return a.v!=b.v?a.v<b.v:a.num>b.num;
}
inline bool operator<=(node a,node b){
    return a.v!=b.v?a.v<b.v:a.num>=b.num;
}
int check(){
    f[0]={0,0},q[0]={1,n,0};
    int L=0,R=0;
    for(int i=1;i<=n;i++){
        while(L<=R&&q[L].r<i)L++;
        f[i]=calc(q[L].id,i);
        if(i==n||calc(q[R].id,n)<calc(i,n))continue;
        while(L<=R&&calc(i,q[R].l)<=calc(q[R].id,q[R].l))R--;
        if(L>R)
            q[++R]={i+1,n,i};
        else{
            int l=q[R].l,r=n,pos=n+1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(calc(i,mid)<=calc(q[R].id,mid))
                    pos=mid,r=mid-1;
                else l=mid+1;
            }
            q[R].r=pos-1,q[++R]={pos,n,i};
        }
    }
    return f[n].num;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>P;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
    int l=0,r=1e18,ans=-1;
    while(l<=r){
        m=(l+r)>>1;
        if(check()>=P)ans=f[n].v-P*m,l=m+1;
        else r=m-1;
    }
    cout<<ans;
}