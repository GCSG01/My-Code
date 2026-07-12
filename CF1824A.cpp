#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int x[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    while(t--){
        int n,m;cin>>n>>m;
        memset(x,0,sizeof x);
        int l=0,r=0,cnt=0;
        for(int i=1,k;i<=n;i++){
            cin>>k;
            if(k==-1)l++;
            else if(k==-2)r++;
            else x[k]=1;
        }
        for(int i=1;i<=m;i++)
            if(x[i])cnt++;
        int ans=min(m,max(cnt+l,cnt+r));
        int s=0;
        for(int i=1;i<=m;i++)
            if(x[i]){
                ans=max(ans,min(i-1,l+s)+min(m-i,r+cnt-s-1)+1);
                s++;
            }
        cout<<ans<<"\n";
    }
    return 0;
}