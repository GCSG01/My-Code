#include<bits/stdc++.h>
using namespace std;
const int N=19;
int n,W,w[N];
int s[1<<N],f[1<<N];
int cst[1<<N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>W;
    for(int i=1;i<=n;i++)cin>>w[i];
    memset(f,0x3f,sizeof f);
    for(int s=0;s<(1<<n);s++)
        for(int i=1;i<=n;i++)
            if(s&(1<<(i-1)))cst[s]+=w[i];
    for(int s=0;s<(1<<n);s++)
        if(cst[s]<=W)
            f[s]=1;
    for(int S=0;S<(1<<n);S++)
        for(int s=S;s;s=(s-1)&S)
            if(cst[s]<=W)f[S]=min(f[S],f[S-s]+1);
    cout<<f[(1<<n)-1];
    return 0;
}