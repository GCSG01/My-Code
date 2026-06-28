#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=5e4+5;
int mu[N],p[N],vis[N],tot;
void init(){
    mu[1]=1;
    for(int i=2;i<=N-5;i++){
        if(!vis[i])
            mu[i]=-1,p[++tot]=i;
        for(int j=1;j<=tot&&i*p[j]<=N-5;j++){
            vis[i*p[j]]=1;
            if(i%p[j])
                mu[i*p[j]]=-mu[i];
            else break;
        }
    }
    return ;
}
int check(int x){
    int ans=0;
    for(int i=1;i*i<=x;i++)
        ans+=x/i/i*mu[i];
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    init();
    while(T--){
        int k;cin>>k;
        int l=k,r=2*k;
        while(l<r){
            int mid=(l+r)>>1;
            if(check(mid)>=k)r=mid;
            else l=mid+1;
        }
        cout<<l<<"\n";
    }
    return 0;
}