#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
int p[N],cnt,sum[N],mu[N];
int n,m;
bitset<N>f;
void init(){
    mu[1]=1;
    for(int i=2;i<=N-5;i++){
        if(!f[i])p[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&p[j]*i<=N-5;j++){
            f[i*p[j]]=1;
            if(i%p[j]==0){
                mu[i*p[j]]=0;break;
            }
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=cnt;i++)
        for(int j=1;p[i]*j<=N-5;j++)
            sum[j*p[i]]+=mu[j];
    for (int i=1;i<=N-5;i++)
        sum[i]+=sum[i-1];
}
int solve(){
    int ans=0,l=1,r=0;
    if(n>m)swap(n,m);
    while(l<=n){
        r=min(n/(n/l),m/(m/l));
        ans+=(sum[r]-sum[l-1])*(n/l)*(m/l);
        l=r+1;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    init();
    int T;cin>>T;
    while(T--)
        cin>>n>>m,cout<<solve()<<"\n";
}