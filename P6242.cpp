#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,INF=1e9+7;
int a[N];
struct node{
    int l,r,mx,hmx,se,cnt,sum,ad1,had1,ad2,had2;
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
void build(int p,int l,int r){
    tr[p].l=l,tr[p].r=r;
    tr[p].ad1=tr[p].had1=tr[p].ad2=tr[p].had2=0;
    if(l==r){
        tr[p].sum=tr[p].mx=tr[p].hmx=a[l];
        tr[p].se=-INF,tr[p].cnt=1;
        return ;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    return 0;
}