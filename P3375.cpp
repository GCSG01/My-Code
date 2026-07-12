#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int kmp[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    string a,b;cin>>a>>b;
    int la=a.size(),lb=b.size();
    a=" "+a,b=" "+b;
    int now=0;
    for(int i=2;i<=lb;i++){
        while(now&&b[now+1]!=b[i])now=kmp[now];
        if(b[now+1]==b[i])now++;
        kmp[i]=now;
    }
    now=0;
    for(int i=1;i<=la;i++){
        while(now&&b[now+1]!=a[i])now=kmp[now];
        if(b[now+1]==a[i])now++;
        if(now==lb)cout<<i-lb+1<<"\n",now=kmp[now];
    }
    for(int i=1;i<=lb;i++)
        cout<<kmp[i]<<" ";
    return 0;
}