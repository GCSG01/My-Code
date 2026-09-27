#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=666623333;
vector<int>p;
bitset<N>vis;
int phi[N],res[N];
void init(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i])p.push_back(i);
        for(int j:p){
            if(i*j>n)break;
            vis[i*j]=1;
            if(i%j==0)break;
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int l,r;cin>>l>>r;
    init(sqrt(r)+1);
    int n=r-l+1;
    for(int i=0;i<n;i++)
        phi[i]=res[i]=l+i;
    for(int x:p){
        int st=(l+x-1)/x*x;
        for(int j=st;j<=r;j+=x){
            int id=j-l;
            phi[id]=phi[id]/x*(x-1);
            while(res[id]%x==0)
                res[id]/=x;
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(res[i]>1)
            phi[i]=phi[i]/res[i]*(res[i]-1);
        ans+=l+i-phi[i],ans%=mod;
    }
    cout<<ans;
}