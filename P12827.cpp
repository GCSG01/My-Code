#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,mod=1e9+7;
int n,q;
int a[N],ans[N];
struct node{
    int op,l,r,x,id;
};
int pw[N];
struct XOR{
    int bas[31],cnt=0;
    void clear(){
        cnt=0;
        memset(bas,0,sizeof bas);
    }
    void insert(int x){
        for(int i=29;~i;i--)
            if((x>>i)&1){
                if(!bas[i])
                    return bas[i]=x,cnt++,void();
                x^=bas[i];
            }
    }
    int query(int x){
        for(int i=29;~i;i--)
            x=max(x,x^bas[i]);
        return x;
    }
    int sol(int len,int x){
        int now=0,del=0,ans=0;
        for(int i=29;~i;i--){
            del+=(bas[i]>0);
            if((x>>i)&1){
                if(((now>>i)&1)&&bas[i])
                    ans+=pw[cnt-del],ans%=mod;
                if(!((now>>i)&1)){
                    ans+=pw[cnt-del],ans%=mod;
                    if(!bas[i])break;
                    now^=bas[i];
                }
            }
            else if(((now>>i)&1)){
                if(!bas[i])break;
                now^=bas[i];
            }
            if(!i)ans++,ans%=mod;
        }
        return ans*pw[len-cnt]%mod;
    }
}pre[N],suf[N];
XOR merge(XOR a,XOR b){
    for(int i=0;i<30;i++)
        if(b.bas[i])
            a.insert(b.bas[i]);
    return a;
}
void solve(int l,int r,vector<node>q){
    if(q.empty())return ;
    if(l==r){
        XOR x;x.clear();x.insert(a[l]);
        for(auto i:q)
            if(!i.op)ans[i.id]=x.sol(1,i.x);
            else ans[i.id]=x.query(i.x);
        return ;
    }
    int mid=(l+r)>>1;
    vector<node>ql,qr;
    pre[mid+1].clear(),suf[mid].clear();
    for(int i=mid;i>=l;i--)
        pre[i].clear(),pre[i]=pre[i+1],pre[i].insert(a[i]);
    for(int i=mid+1;i<=r;i++)
        suf[i].clear(),suf[i]=suf[i-1],suf[i].insert(a[i]);
    XOR x;
    for(auto i:q)
        if(i.r<=mid)ql.push_back(i);
        else if(i.l>mid)qr.push_back(i);
        else{
            x=merge(pre[i.l],suf[i.r]);
            if(!i.op)ans[i.id]=x.sol(i.r-i.l+1,i.x);
            else ans[i.id]=x.query(i.x);
        }
    solve(l,mid,ql),solve(mid+1,r,qr);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    pw[0]=1;
    for(int i=1;i<=500000;i++)pw[i]=pw[i-1]*2ll%mod;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<n;i++)a[i]=a[i]^a[i+1];
        vector<node>qu;
        node x;
        for(int i=1;i<=q;i++)
            cin>>x.op>>x.l>>x.r>>x.x,x.id=i,x.r--,qu.push_back(x);
        solve(1,n-1,qu);
        for(int i=1;i<=q;i++)
            cout<<ans[i]<<"\n";
    }
    return 0;
}