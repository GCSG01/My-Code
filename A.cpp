#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;
int a[N];
vector<int>g[N];
int dfs(int x){
	if(!g[x].size())
        return a[x];
	int mn=INT_MAX;
	for(auto y:g[x])
        mn=min(mn,dfs(y));
	if(a[x]>=mn)
        return mn;
	else return (a[x]+mn)/2;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i],g[i].clear();
        for(int i=2,x;i<=n;i++)
            cin>>x,g[x].push_back(i);
        int mn=INT_MAX;
        for(auto v:g[1])
            mn=min(mn,dfs(v));
        cout<<a[1]+mn<<"\n";
    }
	return 0;
}