#include<bits/stdc++.h>
// #define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=8e5+500;
struct node{
    int l,r;
}a[N];
int n;
int b[N],d[N],dd[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        int ans=0;
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i].l>>a[i].r,b[i]=a[i].l,b[n+i]=a[i].r;
        sort(b+1,b+n*2+1);
        int nn=unique(b+1,b+n*2+1)-b-1;
        for(int i=1;i<=n;i++)
            a[i].l=lower_bound(b+1,b+nn+1,a[i].l)-b,
            a[i].r=lower_bound(b+1,b+nn+1,a[i].r)-b,
            a[i].l*=2,a[i].r*=2,d[a[i].l]++,d[a[i].r+1]--;
        nn*=2,nn+=7;
        for(int i=1;i<=nn;i++)
            d[i]+=d[i-1];
        for(int i=0;i<=nn;i++)
            ans+=(d[i]&&!d[i+1]);
        for(int i=0;i<=nn;i++){
            if(d[i]==1&&d[i-1]!=1)
                dd[i]++;
            if(d[i]==1&&d[i+1]!=1)
                dd[i]++;
        }
        for(int i=1;i<=nn;i++)
            dd[i]+=dd[i-1];
        int sum=INT_MIN;
        for(int i=1;i<=n;i++){
            int cnt=(dd[a[i].r]-dd[a[i].l-1])/2;
            sum=max(sum,cnt-(d[a[i].l]==1)-(d[a[i].r]==1));
        }
        // cout<<ans<<" "<<sum<<"\n";
        cout<<ans+sum<<"\n";
        for(int i=0;i<=nn;i++)
            d[i]=dd[i]=0;
    }
    return 0;
}