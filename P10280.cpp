#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
set<pair<int,int>>st[2];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,k;cin>>n>>k;
    string a,b;cin>>a>>b;
    a=" "+a,b=" "+b;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(a[i]==b[i])continue;
        int x=a[i]-'0';
        if(st[!x].empty())st[x].insert({i%k,i});
        else{
            auto cnt=st[!x].lower_bound(make_pair(i%k,0ll));
            if(cnt==st[!x].end())cnt=st[!x].begin();
            int j=(*cnt).second;
            ans+=(i-j+k-1)/k;
            st[!x].erase(cnt);
        }
    }
    cout<<ans;
    return 0;
}