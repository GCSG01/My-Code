#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int n,mxk;
int vis[N];
vector<int>a[12];
bitset<1005>b[10];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>mxk;
    if(n==1)return cout<<"2"<<endl<<1<<endl,0;
    int bas=1,tot=0;
    for(int i=1;i<=10;i++){
        tot++;
        for(int j=1;j<=n;j++)
            if(j&bas)a[i].push_back(j);
        if(!a[i].size())continue;
        cout<<"1 "<<a[i].size();
        for(int j:a[i])cout<<" "<<j;
        cout<<endl;
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=10;j++)
            if(j&(1<<(i-1)))
                for(int k:a[j])b[i][k]=b[i][k]^1;
        cout<<"1 "<<b[i].size();
        for(int j=1;j<=1000;j++)
            if(b[i][j])cout<<" "<<j;
        cout<<endl;
    }
    cout<<2<<endl;
    for(int i=1,x;i<=tot;i++){
        int sum=0;
        cin>>x;sum+=x;
        cin>>x;sum+=x;
        cin>>x;sum+=x;
        if(sum<=1)vis[i]=1;
    }
    int ans=0;
    for(int j=1;j<=10;j++)
        if(vis[j])ans|=(1<<(j-1));
    cout<<ans;
    return 0;
}