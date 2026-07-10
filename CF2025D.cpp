#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,M=5e3+5;
int n,m;
int r[N];
int f[M];
int a[M];
void add(int x,int y){
    if(x>y||x<0||y>m)return ;
    return a[x]++,a[y+1]--,void();
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>r[i];
    int s=0;
    for(int i=1;i<=n;i++)
        if(r[i]>0)add(r[i],s);
        else if(r[i]<0)add(0,s+r[i]);
        else{
            s++;
            f[0]+=a[0];
            for(int j=1;j<=s;j++)a[j]+=a[j-1];
            for(int j=1;j<=s;j++)f[j]+=a[j];
            for(int j=s;j>=1;j--)f[j]=max(f[j],f[j-1]);
            memset(a,0,sizeof a);
        }
    int ans=0;
    f[0]+=a[0];
    for(int i=1;i<=m;i++)a[i]+=a[i-1];
    for(int i=1;i<=m;i++)f[i]+=a[i];
    for(int i=0;i<=m;i++)ans=max(ans,f[i]);
    cout<<ans;
    return 0;
}