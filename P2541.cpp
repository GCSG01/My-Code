#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k,m[N],p[N][12];
priority_queue<pair<int,pair<int,int>>>pq;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>m[i];
        for(int j=1;j<=m[i];j++)
            cin>>p[i][j];
        sort(p[i]+1,p[i]+m[i],1);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        pq.push({p[i][1],{i,1}});
    for(int i=1;i<=k;i++){}
    return 0;
}