#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n;
int a[N],f[N];
vector<int>g[N];
bool check(int x){
	if(x-a[x]>=1&&abs(a[x]-a[x-a[x]])%2)
        return 1;
	if(x+a[x]<=n&&abs(a[x]-a[x+a[x]])%2)
        return 1;
	return 0;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	queue<int>q;
	memset(f,-1,sizeof(f));
	for(int i=1;i<=n;i++)
        cin>>a[i];
	for(int i=1;i<=n;i++){
		if(i-a[i]>0)
            g[i-a[i]].push_back(i);
		if(i+a[i]<=n)
            g[i+a[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
		if(check(i))
            f[i]=1,q.push(i);
	while(q.size()){
		int u=q.front();q.pop();
		for(int i:g[u])
			if(f[i]==-1)
                q.push(i),f[i]=f[u]+1;
	}
	for(int i=1;i<=n;i++)
        cout<<f[i]<<" ";
	return 0;
}