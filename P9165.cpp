#include<bits/stdc++.h>
#define ll long long
// #define int long long
using namespace std;
const int p=998244353;
int m=750,st=5,n=100;
ll iv[355];
ll inv(ll a,int b=p-2){
    ll res=1;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p,b>>=1;
    }
    return res;
}
vector<int> work(vector<pair<ll,ll>> a){
	vector<int>res(n),f(n+1);
	if(!iv[n+1])
		for(int i=-155;i<=155;i++)
			iv[i+160]=inv(i+p);
	f[0]=1;
	for(int i=0;i<n;i++)
		for(int j=n;j>=0;j--){
			f[j]=(p-a[i].first)*f[j]%p;
			if(j)f[j]=(f[j]+f[j-1])%p;
		}
	for(int i=0;i<n;i++){
		ll c=a[i].second;
		for(int j=0;j<n;j++)
            if(i!=j)
                c=c*iv[a[i].first-a[j].first+160]%p;
		vector<int>g(n+1);
		for(int j=n-1;j>=0;j--)
			g[j]=(f[j+1]+a[i].first*g[j+1])%p;
		for(int j=0;j<n;j++)
			res[j]=(res[j]+c*g[j])%p;
	}
	return res;
}
vector<int> Decode(vector<int> a){
	vector<pair<ll,ll>>ans;
	for(int i=1;i*st<=m;i++){
		map<int,int>M;
		for(int j=(i-1)*st;j<i*st;j++)
			M[a[j]]++;
		for(auto j:M)
            if(j.second>=2)
                ans.push_back(make_pair(i,j.first));
	}
	ans.resize(100);
	return work(ans);
}
vector<int> Encode(vector<int> a){
	auto f=[&](int x){
		ll ans=0;
		for(int i=n-1;i>=0;i--)
			ans=(ans*x+a[i])%p;
		return ans;
	};
	vector<int>ans;
	for(int i=1;i*st<=m;i++){
		int v=f(i);
		for(int j=1;j<=st;j++)
            ans.push_back(v);
	}
	return ans;
} 