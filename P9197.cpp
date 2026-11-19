#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105,L=1e3+5,mod=1e9+7;
int n,l,a[N];
int f[N][L][2][2];
int g[N][L][2][2];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>l;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,[](int A,int B){return A>B;});
	for(int p=0;p<=1;p++)
		for(int q=0;q<=1;q++)
			f[1][0][p][q]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++)
			for(int k=0;k<=l;k++)
				for(int p=0;p<=1;p++)
					for(int q=0;q<=1;q++)
						g[j][k][p][q]=f[j][k][p][q],f[j][k][p][q]=0;
		for(int j=1;j<i;j++)
			for(int k=0;k<=l;k++)
				for(int p=0;p<=1;p++)
					for(int q=0;q<=1;q++){
						if(!g[j][k][p][q])continue;
						int cnt=k+(2*j-p-q)*(a[i-1]-a[i]);
						if(cnt>l)continue;
						if(j>1)
							(f[j+1][cnt][p][q]+=(j-1)*g[j][k][p][q]%mod)%=mod,
							(f[j][cnt][p][q]+=2*(j-1)*g[j][k][p][q]%mod)%=mod,
							(f[j-1][cnt][p][q]+=(j-1)*g[j][k][p][q]%mod)%=mod;
						if(!p)
							(f[j+1][cnt][0][q]+=g[j][k][p][q])%=mod,
							(f[j+1][cnt][1][q]+=g[j][k][p][q])%=mod,
							(f[j][cnt][0][q]+=g[j][k][p][q])%=mod,
							(f[j][cnt][1][q]+=g[j][k][p][q])%=mod;
						if(!q)
							(f[j+1][cnt][p][0]+=g[j][k][p][q])%=mod,
							(f[j+1][cnt][p][1]+=g[j][k][p][q])%=mod,
							(f[j][cnt][p][0]+=g[j][k][p][q])%=mod,
							(f[j][cnt][p][1]+=g[j][k][p][q])%=mod;
					}
	}
	int ans=0;
	for(int i=0;i<=l;i++)
		ans+=f[1][i][1][1],ans%=mod;
	cout<<ans;
}