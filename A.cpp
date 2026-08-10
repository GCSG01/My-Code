#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=19990721,N=1005;
int a[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)a[i]=1;
    int lst=0;
    while(m--){
        int o;cin>>o;
        if(!o){
            int x,y;cin>>x>>y;
            int l=(x+lst)%n+2,r=(y+lst)%n+2;
            for(int i=l;i<=r;i++)
                a[i]=-a[i];
        }
        else{
            int x,y,k;cin>>x>>y>>k;
            int l=(x+lst)%n+1,r=(y+lst)%n+1,ans=0;
            if(!k)ans=1;
            else if(k>1)ans=2;
            else{
                int s1=1,s2=1;
                for(int i=l+1;i<=r;i++)
                    if(a[i]==1)(s1+=s2)%=mod;
                    else (s2+=s1)%=mod;
                ans=(s1+s2)%mod;
            }
            cout<<(lst=ans)<<"\n";
        }
    }
    return 0;
}