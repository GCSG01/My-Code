#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
struct node{
    int l,r;
}a[N];
int x[N];
int s0[N],s1[N],s2[N];
int n,k;
int get0(int l,int r){return l>r?0:s0[r]-s0[l-1];}
int get1(int l,int r){return l>r?0:s1[r]-s1[l-1];}
int get2(int l,int r){return l>r?0:s2[r]-s2[l-1];}
struct TREE{
    int v0,v1,v0l,v0r,v1l,v1r,l,r;
    TREE operator+(const TREE &B)const{
        if(B.l==-1)return *this;
        if(l==-1)return B;
        return (TREE){
            max({v0+get1(B.l,B.r),get1(l,r)+B.v0,v0r+B.v0l}),
            max({v1+get2(B.l,B.r),get2(l,r)+B.v1,v1r+B.v1l}),
            max(get0(l,r)+B.v0l,v0l+get1(B.l,B.r)),
            max(v0r+get0(B.l,B.r),get1(l,r)+B.v0r),
            max(get1(l,r)+B.v1l,v1l+get2(B.l,B.r)),
            max(v1r+get1(B.l,B.r),get2(l,r)+B.v1r),
            l,B.r
        };
    }
}tr[N<<2];
#define ls(p) (p)<<1
#define rs(p) (p)<<1|1
void build(int l,int r,int p){
    if(l==r){
        tr[p].l=l,tr[p].r=r;
        tr[p].v0=tr[p].v0l=tr[p].v0r=(x[l]==k-1||x[l]==k);
        tr[p].v1=tr[p].v1l=tr[p].v1r=(x[l]==k+1||x[l]==k);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,ls(p)),build(mid+1,r,rs(p));
    tr[p]=tr[ls(p)]+tr[rs(p)];
    return ;
}
TREE query(int l,int r,int p,int ll,int rr){
	if(ll<=l&&r<=rr)
		return tr[p];
	else if(ll<=r&&l<=rr){
        int mid=(l+r)>>1;
		return query(l,mid,ls(p),ll,rr)+query(mid+1,r,rs(p),ll,rr);
	}
    return (TREE){0,0,0,0,0,0,-1,-1};
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n*2;i++)x[i]=0;
        for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r,x[a[i].l]++,x[a[i].r+1]--;
        for(int i=1;i<=n*2;i++)x[i]+=x[i-1];
        for(int i=1;i<=n*2;i++)
        s0[i]=s0[i-1]+(x[i]==k-1),
        s1[i]=s1[i-1]+(x[i]==k),
        s2[i]=s2[i-1]+(x[i]==k+1);
        build(1,n*2,1);
        for(int i=1;i<=n;i++){
            TREE l=query(1,n*2,1,1,a[i].l-1),m=query(1,n*2,1,a[i].l,a[i].r),r=query(1,n*2,1,a[i].r+1,n*2);
            cout<<max({
                get1(1,a[i].l-1)+m.v1+get1(a[i].r+1,2*n),
                get1(1,a[i].l-1)+m.v1r+r.v0l,
                l.v0r+m.v1l+get1(a[i].r+1,2*n),
                get1(1,a[i].l-1)+get2(a[i].l,a[i].r)+r.v0,
                l.v0+get2(a[i].l,a[i].r)+get1(a[i].r+1,2*n),
                l.v0r+get1(a[i].l,a[i].r)+r.v0l,
            })<<"\n";
        }
    }
    return 0;
}