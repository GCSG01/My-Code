#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+5;
int n,m,z[N],p[N];
string a,b;
void Z(){
    for(int i=1;i<=m;i++)z[i]=0;
    z[1]=m;
    int l=0,r=0;
    for(int i=2;i<=m;i++){
        if(i<=r)z[i]=min(z[i-l+1],r-i+1);
        while(i+z[i]<=m&&b[i+z[i]]==b[z[i]+1])z[i]++;
        if(i+z[i]-1>r)r=i+z[i]-1,l=i;
    }
    return ;
}
void exkmp(){
    Z();
    for(int i=1;i<=n;i++)p[i]=0;
    int l=0,r=0;
    for(int i=1;i<=n;i++){
        if(i<=r)p[i]=min(z[i-l+1],r-i+1);
        while(i+p[i]<=n&&a[i+p[i]]==b[p[i]+1])p[i]++;
        if(i+p[i]-1>r)r=i+p[i]-1,l=i;
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>a>>b;
    n=a.size(),m=b.size();
    a=" "+a,b=" "+b;
    exkmp();
    int ans=0;
    for(int i=1;i<=m;i++)ans^=i*(z[i]+1);
    cout<<ans<<"\n",ans=0;
    for(int i=1;i<=n;i++)ans^=i*(p[i]+1);
    cout<<ans;
    return 0;
}