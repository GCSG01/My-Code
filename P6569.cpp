#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=101;
int n,m,q,f[N];
struct mat{
	bitset<N>a[N];
	mat friend operator*(mat a,mat b){
		mat c;
		for(int i=1;i<=n;i++)
			for(int k=1;k<=n;k++)
				if(a.a[i][k])c.a[i]^=b.a[k];
		return c;
	}
	mat friend operator^(mat a,int b){
		mat ans=a;b--;
		while(b){
			if(b&1)ans=ans*a;
			a=a*a,b>>=1;
		}
		return ans;
	}
}ans,bit;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>f[i];
    for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,bit.a[u][v]=bit.a[v][u]=1;
	while(q--){
        int x;cin>>x,ans=bit^x;
        int sum=0;
		for(int i=1;i<=n;i++)
            if(ans.a[1][i])sum^=f[i];
		cout<<sum<<"\n";
	}
}