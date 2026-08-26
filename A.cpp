#include<bits/stdc++.h>
using namespace std;
int a[6565465];
int f[6556];
int mex(int l,int r){
    memset(f,0,sizeof f);
    for(int i=l;i<=r;i++)f[a[i]]=1;
    int x=0;
    for(int i=1;i<=400;i++)
        if(f[x])x++;
    if(x==6)
        for(int i=l;i<=r;i++)
            cout<<a[i]<<"\n";
    return x;
}
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            ans^=mex(i,j);
    cout<<ans;
}