#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,k,P=1,tot,cnt,sum,p[N],a[N],f[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;

    if(!k){for(int i=1;i<=n;i++)cout<<"1 ";return 0;}
    if(n==2&&k==1)return cout<<"0 0",0;
    if(n==2&&k==2)return cout<<-1,0;

    while((P<<1)<=n)P<<=1;
    if(k>=P*2)return cout<<-1,0;

    if(n&1)k^=P+1;
    for(int i=1;i<=P;i++)p[i]=1,cnt++,tot++;
    for(int i=P;i>=1;i--)
        if((i^1^k)<k)k^=i^1,p[i]=i,cnt--;
    if(n&1)p[P+1]=P+1,tot++;

    sort(p+1,p+tot+1);
    if(k)p[1]=2,p[2]=3;
    sort(p+1,p+tot+1);

    cnt=0,a[0]=0,f[p[tot]]=1;
    for(int i=1;i<tot;i++)
        if(p[i]!=p[i+1])
            a[i+1]=p[i],f[p[i]]=1;
    for(int i=1;i<=tot;i++)
        if(!a[i]){
            while(f[cnt])cnt++;
            a[i]=cnt,f[cnt]=1;
        }

    for(int i=1;i<=min(n,tot);i++)cout<<a[i]<<" ";
    for(int i=tot+1;i<=n;i++)cout<<n<<" ";
    return 0;
}