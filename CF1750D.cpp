#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,p=998244353;
int n,m;
int a[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        int flag=0;
        for(int i=2;i<=n;i++)
            if(a[i-1]%a[i]){
                flag=1;break;
            }
        if(flag){
            cout<<"0\n";continue;
        }
        int ans=1;
        for(int i=2;i<=n;i++){
            int d=a[i-1]/a[i];
            vector<int>tmp;
            for(int j=2;j*j<=d;j++)
                if(d%j==0){
                    int sz=tmp.size();
                    for(int k=0;k<sz;k++)tmp.push_back(-tmp[k]*j);
                    tmp.push_back(j);
                    while(d%j==0)d/=j;
                }
            if(d>1){
                int sz=tmp.size();
                for(int k=0;k<sz;k++)tmp.push_back(-tmp[k]*d);
                tmp.push_back(d);
            }
            int s=ans,tot=m/a[i];
            ans*=tot,ans%=p;
            for(int j:tmp)
                ans-=tot/j*s,ans%=p;
            if(ans<0)ans+=p;
        }
        cout<<ans<<"\n";
    }
    return 0;
}