#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1<<19;
int n;
int a[N],mx1[N],mx2[N];
void upd(int &x,int &y,int v){
    if(v>x)y=x,x=v;
    else y=max(y,v);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int m;cin >> m,n=1<<m;
    for(int i=0;i<n;i++)
        cin>>a[i],mx1[i]=a[i],mx2[i]=-1145141919810;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            if(j&(1<<i))
                upd(mx1[j],mx2[j],mx1[j^(1<<i)]),
                upd(mx1[j],mx2[j],mx2[j^(1<<i)]);
    int ans=mx1[0]+mx2[0];
    for(int k=1;k<n;k++)
        ans=max(ans,mx1[k]+mx2[k]),cout<<ans<<"\n";
}