#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
int a[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        int op;cin>>op;
        if(op==1){
            int x,y;cin>>x>>y;
            for(int i=1;i<=n;i++)
                if(a[i]==x)a[i]=y;
        }
        else{
            int ans=0;
            for(int i=1;i<=n;i++)
                if(a[i]!=a[i-1])ans++;
            cout<<ans<<"\n";
        }
    }
    return 0;
}