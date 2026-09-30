#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int phi[N],p[N],cnt=0,f[N],vis[N];
int a[N],tot;
void init(){
	phi[1]=1;
	for(int i=2;i<=N-5;i++){
		if(!f[i])p[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&p[j]*i<=N-5;j++){
			f[p[j]*i]=1;
			if(i%p[j]==0){
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	vis[2]=vis[4]=1;
	for(int i=2;i<=cnt;i++){
		for(int j=1;j*p[i]<=N-5;j*=p[i])
			vis[j*p[i]]=1;
		for(int j=2;j*p[i]<=N-5;j*=p[i])
			vis[j*p[i]]=1;
	}
}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int qpow(int x,int y,int mod){
	int s=1;
	while(y){
		if(y&1)s*=x,s%=mod;
		x*=x,x%=mod,y>>=1;
	}
	return s;
}
bool check(int x,int ph){
	if(qpow(x,phi[ph],ph)!=1)return 0;
	for(int i=1;i<=tot;i++)
		if(qpow(x,phi[ph]/a[i],ph)==1)
			return 0;
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t,init();
	while(t--){
		int n,D;cin>>n>>D;
		if(vis[n]){
			int ph=phi[n];
			tot=0;
			for(int i=1;p[i]*p[i]<=ph;i++)
				if(ph%p[i]==0){
					a[++tot]=p[i];
					while(ph%p[i]==0)ph/=p[i];
				}
			if(ph!=1)a[++tot]=ph;
			int mn=-1;
			for(int i=1;i<n;i++)
				if(check(i,n)){
					mn=i;break;
				}
			int s=1;
			vector<int>ans;
			for(int i=1;i<=phi[n];i++){
				s=s*mn%n;
				if(gcd(i,phi[n])==1)
					ans.push_back(s);
			}
			sort(ans.begin(),ans.end());
			cout<<ans.size()<<"\n";
			for(int i=1;i<=ans.size()/D;i++)
				cout<<ans[i*D-1]<<" ";
			cout<<"\n";
		}
		else cout<<"0\n\n";
	}
}