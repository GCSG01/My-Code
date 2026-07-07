#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int n,m;
int a[N*N];
int b[N*N];
int ans[N];
unordered_map<int,int>t;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n*n;i++){
        cin>>a[i],t[a[i]]++;
        if(t[a[i]]==1)b[++m]=a[i];
    }
    sort(b+1,b+m+1,[](int A,int B){return A>B;});
    int x=0;
    for(int i=1;i<=m&&x<n;){
        while(!t[b[i]])i++;
        ans[++x]=b[i],t[b[i]]--;
        for(int j=1;j<x;j++)
            t[__gcd(ans[j],ans[x])]-=2;
    }
    for(int i=1;i<=x;i++)cout<<ans[i]<<" ";
    return 0;
}