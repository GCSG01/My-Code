#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct ST{
    struct node{
        int mn,mx,L,R;
    };
    int n,inf; node t[N*4];
    ST(int n):n(n),inf(n+1){bd(1,n,1);}
    int cv(int x,int l,int r){return min(r,max(l,x));}
    void bd(int l,int r,int p){t[p]={inf,0,1,n};if(l==r)return;int m=(l+r)>>1;bd(l,m,p<<1);bd(m+1,r,p<<1|1);}
    void ap(int p,int L,int R){
        if(t[p].mn<=n)t[p].mn=cv(t[p].mn,L,R);
        if(t[p].mx>=1)t[p].mx=cv(t[p].mx,L,R);
        t[p].L=cv(t[p].L,L,R);t[p].R=cv(t[p].R,L,R);
    }
    void ps(int l,int r,int p){
        if(l==r||(t[p].L==1&&t[p].R==n))return;
        ap(p<<1,t[p].L,t[p].R);ap(p<<1|1,t[p].L,t[p].R);
        t[p].L=1;t[p].R=n;
    }
    void pl(int p){t[p].mn=min(t[p<<1].mn,t[p<<1|1].mn);t[p].mx=max(t[p<<1].mx,t[p<<1|1].mx);}
    void upd(int l,int r,int p,int ql,int qr,int L,int R){
        if(qr<l||r<ql)return;
        if(ql<=l&&r<=qr){ap(p,L,R);return;}
        ps(l,r,p);int m=(l+r)>>1;
        upd(l,m,p<<1,ql,qr,L,R);upd(m+1,r,p<<1|1,ql,qr,L,R);pl(p);
    }
    void upd(int l,int r,int L,int R){if(l<=r)upd(1,n,1,l,r,L,R);}
    pair<int,int> qry(int l,int r,int p,int ql,int qr){
        if(qr<l||r<ql)return {inf,0};
        if(ql<=l&&r<=qr)return {t[p].mn,t[p].mx};
        ps(l,r,p);int m=(l+r)>>1;
        auto x=qry(l,m,p<<1,ql,qr),y=qry(m+1,r,p<<1|1,ql,qr);
        return {min(x.first,y.first),max(x.second,y.second)};
    }
    pair<int,int> qry(int l,int r){return l>r?pair<int,int>{inf,0}:qry(1,n,1,l,r);}
    void sp(int l,int r,int p,int x,int L,int R){
        if(l==r){t[p]={L,R,1,n};return;}
        ps(l,r,p);int m=(l+r)>>1;
        if(x<=m)sp(l,m,p<<1,x,L,R);else sp(m+1,r,p<<1|1,x,L,R);pl(p);
    }
    void sp(int x,int L,int R){sp(1,n,1,x,L,R);}
    pair<int,int> gp(int l,int r,int p,int x){
        if(l==r)return {t[p].mn,t[p].mx};
        ps(l,r,p);int m=(l+r)>>1;
        return x<=m?gp(l,m,p<<1,x):gp(m+1,r,p<<1|1,x);
    }
    pair<int,int> gp(int x){return gp(1,n,1,x);}
};

int a[N], b[N];
long long d[N+2];

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    for(int i=0;i<n;++i)cin>>a[i];
    for(int i=0;i<n;++i)cin>>b[i];
    ST st(n);st.sp(a[0],b[0],b[0]);
    for(int i=1;i<n;++i){
        int A=a[i],B=b[i];
        auto left=st.qry(1,A-1),right=st.qry(A+1,n);
        int nl=n+1,nr=0;
        if(right.first<=n){nl=min(nl,min(right.first,B));nr=max(nr,min(right.second,B));}
        if(left.first<=n){nl=min(nl,max(left.first,B));nr=max(nr,max(left.second,B));}
        st.upd(1,A-1,1,B);st.upd(A+1,n,B,n);st.sp(A,nl,nr);
    }
    memset(d,0,sizeof(long long)*(n+2));
    auto add=[&](int l,int r){if(l<=r){++d[l];--d[r+1];}};
    for(int x=1;x<=n;++x){
        auto [L,R]=st.gp(x);
        if(L<=x)add(x-min(R,x),x-L);
        if(R>x)add(max(L,x+1)-x,R-x);
    }
    long long cur=0;
    for(int k=0;k<n;++k)cur+=d[k],cout<<cur<<" ";
}