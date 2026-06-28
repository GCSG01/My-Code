#include<bits/stdc++.h>
using namespace std;
const int N=24,mod=1e9+7;
int n,m;
int a[1<<N],b[4];
int f[1<<N];
inline int lowbit(int x){return x&-x;}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<(1<<n);i<<=1)
        cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++)
        cin>>b[i];
    f[0]=1;
    for(int s=1;s<(1<<n);s++){
        a[s]=a[lowbit(s)^s]+a[lowbit(s)];
        if(b[1]==a[s]||b[2]==a[s])continue;
        for(int i=s;i;i^=lowbit(i))
            f[s]+=f[s^lowbit(i)],f[s]%=mod;
    }
    cout<<f[(1<<n)-1];
    return 0;
}