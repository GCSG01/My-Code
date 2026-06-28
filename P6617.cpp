#include<bits/stdc++.h>
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=5e5+5;
int a[N];
int n,m,w;
int tr[N<<2];
#define ls p<<1
#define rs p<<1|1
void update(int l,int r,int p,int x,int y){
    if(l==r)return tr[p]=y,void();
    int mid=(l+r)>>1;
    if(x<=mid)update(l,mid,ls,x,y);
    else update(mid+1,r,rs,x,y);
    tr[p]=max(tr[ls],tr[rs]);
    return ;
}
int query(int l,int r,int p,int ll,int rr){
    if(ll<=l&&r<=rr)return tr[p];
    int mid=(l+r)>>1,st=0;
    if(ll<=mid)st=max(st,query(l,mid,ls,ll,rr));
    if(rr>mid)st=max(st,query(mid+1,r,rs,ll,rr));
    return st;
}
#undef ls
#undef rs
set<int>st[N];
int get(int x){
    auto it1=st[a[x]].lower_bound(x),it2=st[w-a[x]].lower_bound(x);
    if(it2==st[w-a[x]].begin())return 0;
    if(it1==st[a[x]].begin())return *(--it2);
    it1--,it2--;
    if(*it1>*it2)return 0;
    return *it2;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(m),rd(w);
    for(int i=1;i<=n;i++)
        rd(a[i]),update(1,n,1,i,get(i)),st[a[i]].insert(i);
    int sans=0;
    while(m--){
        int op,l,r;rd(op),rd(l),rd(r);
        if(op==1){
            vector<int> upd;
            // cout<<"Update\n";
            auto it=st[a[l]].upper_bound(l);
            if(it!=st[a[l]].end())
                upd.push_back(*it);
            it=st[w-a[l]].upper_bound(l);
            if(it!=st[w-a[l]].end())
                upd.push_back(*it);
            st[a[l]].erase(l);
            st[a[l]=r].insert(l);
            upd.push_back(l);
            it=st[a[l]].upper_bound(l);
            if(it!=st[a[l]].end())
                upd.push_back(*it);
            it=st[w-a[l]].upper_bound(l);
            if(it!=st[w-a[l]].end()) upd.push_back(*it);
            for(auto p:upd){
                // cout<<p<<" "<<get(p)<<"\n";
                update(1,n,1,p,get(p));
            }
            // cout<<"\n";
        }
        else{
            l^=sans,r^=sans;
            // cout<<l<<" "<<r<<"\n";
            int ans=query(1,n,1,l,r);
            // cout<<ans<<" ";
            if(ans>=l)cout<<"Yes\n",sans++;
            else cout<<"No\n";
        }
    }
    return 0;
}