#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const int N=3e7+5;
int phi[N],n;
ull sum[N];
vector<int>p;
bitset<N>f;
void init(){
    phi[1]=1;
    for(int i=2;i<=N-5;i++){
        if(!f[i])p.push_back(i),phi[i]=i-1;
        for(int j:p){
            if(j*i>N-5)break;
            f[j*i]=1;
            if(i%j==0){
                phi[j*i]=phi[i]*j;break;
            }
            else phi[j*i]=phi[i]*(j-1);
        }
    }
    for(int i=1;i<=N-5;i++)
        sum[i]=sum[i-1]+1ull*phi[i]*i*i*i;
}
ull solve(int n){
    ull ans=0;
    int l=1,r=0;
    while(l<=n){
        ull cnt=(n/l)*(n/l+1)/2;
        r=n/(n/l);
        ans+=(sum[r]-sum[l-1])*cnt*cnt*cnt;
        l=r+1;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T,init();
    while(T--)
        cin>>n,cout<<solve(n)<<"\n";
}