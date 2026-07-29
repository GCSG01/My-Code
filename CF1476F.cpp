#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,a[N];
int tr[N<<2];
int from[N],ans[N],f[N];
#define ls p<<1
#define rs p<<1|1
#define mid (l+r)/2
void build(int l,int r,int p){
    if(l==r)
        return tr[p]=a[l],void();
    build(l,mid,ls),build(mid+1,r,rs);
    return tr[p]=min(tr[ls],tr[rs]),void();
}
int query(int l,int r,int p,int s,int t){
    if(s<=l&&r<=t)return tr[p];
    int mn=INT_MAX;
    if(s<=mid)mn=min(mn,query(l,mid,ls,s,t));
    if(t>mid)mn=min(mn,query(mid+1,r,rs,s,t));
    return mn;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i],from[i]=-1;
        vector<int>v;
        build(1,1,n);
        v.push_back(0);
        for(int i=1;i<=n;i++){
            f[i]=f[i-1];
            int pos=lower_bound(v.begin(),v.end(),i-a[i]-1)-v.begin();
            if(pos!=i){
                int val=max(query(1,1,n,pos+1,i-1),i-1);
                if(f[i]<val)
                    f[i]=val,from[i]=pos;
            }
            if(f[i-1]>=i&&i+a[i]>=f[i])
                f[i]=i+a[i],from[i]=-1;
            v.push_back(f[i]);
        }
        if(f[n]>=n){
            cout<<"YES\n";
            for(int i=n;i;i--)
                if(from[i]==-1)
                    ans[i]='R';
                else{
                    ans[i]='L';
                    for(int j=from[i]+1;j<i;j++)
                        ans[j]='R';
                    i=from[i]+1;
                }
            for(int i=1;i<=n;i++)
                cout<<ans[i];
            cout<<"\n";
        }
        else cout<<"NO\n";
    }
    return 0;
}