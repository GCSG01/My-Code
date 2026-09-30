#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,pos[N],col[N];
string s;
struct node{
    int cnt[N],l,r,ans;
    node():l(1),r(0),ans(0){memset(cnt,0,sizeof cnt);}
    inline int w(int ql,int qr){
        if(ql>qr)return 0;
        while(l>ql){
            l--;
            if(s[l]=='('&&pos[l]<=r)ans+=(++cnt[col[l]]);
        }
        while(r<qr){
            r++;
            if(s[r]==')'&&pos[r]>=l)ans+=(++cnt[col[r]]);
        }
        while(l<ql){
            if(s[l]=='('&&pos[l]<=r)ans-=cnt[col[l]]--;
            l++;
        }
        while(r>qr){
            if(s[r]==')'&&pos[r]>=l)ans-=cnt[col[r]]--;
            r--;
        }
        return ans;
    }
}A,B;
int f[N],mid;
int cnt[N],p[N];
inline void checkA(int i,int j){
    int x=f[j]+A.w(j+1,i)+mid;
    if(x<f[i])f[i]=x,cnt[i]=cnt[j]+1,p[i]=j;
    else if(x==f[i]&&cnt[j]+1<cnt[i])cnt[i]=cnt[j]+1,p[i]=j;
}
inline void checkB(int i,int j){
    int x=f[j]+B.w(j+1,i)+mid;
    if(x<f[i])f[i]=x,cnt[i]=cnt[j]+1,p[i]=j;
    else if(x==f[i]&&cnt[j]+1<cnt[i])cnt[i]=cnt[j]+1,p[i]=j;
}
void solve(int l,int r){
    if(r-l<=1)return;
    int mid=(l+r)>>1;
    for(int i=p[l];i<=p[r];i++)checkA(mid,i);
    solve(l,mid);
    for(int i=l+1;i<=mid;i++)checkB(r,i);
    solve(mid,r);
}
inline bool check(){
    for(int i=1;i<=n;i++)f[i]=1e18,cnt[i]=p[i]=0;
    checkA(n,0),solve(0,n);
    return cnt[n]<=m;
}
int st[N],tp,id;
int l,r,ans;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>s,s=" "+s;
    for(int i=1;i<=n;i++){
        if(s[i]=='('){
            st[++tp]=i,pos[i]=n+1;
            continue;
        }
        if(!tp)continue;
        int j=st[tp--];
        pos[i]=j,pos[j]=i;
        col[i]=col[j]=(col[j-1]?col[j-1]:++id);
    }
    l=0,r=1e10;
    while(l<=r){
        mid=(l+r)>>1;
        if(check())r=mid-1,ans=mid;
        else l=mid+1;
    }
    mid=ans,check();
    cout<<f[n]-mid*m;
}