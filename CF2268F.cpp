#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=220;
int n,a[N][N];
int vis[N],chose[N];
vector<pair<int,int>>ans;
void swp(int x,int y){
	ans.push_back({x,y});
	swap(a[x][y],a[x+1][y]);
	swap(a[x][y+1],a[x+1][y+1]);
}
int find(int j,int x){
	for(int i=1;i<=n;i++)
		if(a[i][j]==x)return i;
	return -1;
}
void solve(int i,int to,int mx){
	int pos=min(i+to,i);
	int p1=1,p2=1;
	while(a[p1][i]!=mx)p1++;
	while(a[p2][i+to]!=mx)p2++;
	if(p1<p2){
		if(p1==mx-1)swp(mx-2,pos),p1--;
		if(p2==mx)swp(mx-1,pos),p2--;
		while(p1<p2-1)swp(p1,pos),p1++;
		swp(p1,min(i+to,i+to*2)),p2--;
	}
	if(p1>p2){
		if(p2==mx-1)swp(mx-2,pos),p2--;
		if(p1==mx)swp(mx-1,pos),p1--;
		while(p2<p1)
			swp(p2,min(i+to,i+to*2)),p2++;
	}
	while(p1<mx)swp(p1,pos),p1++;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n,n=n*2,ans.clear();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>a[i][j];
		int flag=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=j+1;k<=n;k++)
					flag+=a[j][i]>a[k][i];
		if(flag&1){
			cout<<"-1\n";continue;
		}
		for(int mx=n;mx>=3;mx--){
			for(int i=1;i<mx;i++){
				for(int j=3;j<=n-2;j++)
					vis[j]=(a[i][j]==mx);
				chose[2]=0;
				for(int j=3;j<=n-2;j++)
					chose[j]=vis[j]^chose[j-1];
				int sum=0;
				for(int j=2;j<=n-2;j++)
					sum+=chose[j];
				if(2*sum>n-3){
					chose[2]=1;
					for(int j=3;j<=n-2;j++)
						chose[j]=vis[j]^chose[j-1];
				}
				for(int j=2;j<=n-2;j++)
					if(chose[j])swp(i,j);
			}
			solve(1,1,mx);
			solve(n,-1,mx);
		}
		for(int i=1;i<n;i++)
			if(a[1][i]!=1)swp(1,i);
		cout<<ans.size()<<"\n";
		for(auto i:ans)
			cout<<i.first<<" "<<i.second<<"\n";
	}
}