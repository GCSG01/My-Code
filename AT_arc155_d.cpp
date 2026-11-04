#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,a[N];
int cnt[N],cnt2[N];
vector<int>v[N];
bitset<N>SG[3];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],cnt[a[i]]++;
	for(int i=2;i<=N-5;i++)v[i].reserve(log2(N-5));
	for(int i=2;i<=N-5;i++)
		for(int j=i;j<=N-5;j+=i)
			v[j].push_back(i);
	for(int i=2;i<=N-5;i++)
		for(int j=i+i;j<=N-5;j+=i)
			cnt[i]+=cnt[j];
	for(int i=2;i<=N-5;i++){
		int flag=0;
		for(int j:v[i])
			cnt2[j]=cnt[j];
		for(int j=(int)v[i].size()-1;j>=0;j--){
			int x=v[i][j];
			if (j<v[i].size()-1&&cnt2[x]){
				if(!SG[1][x])SG[0][i]=1;
				if(!SG[0][x])SG[1][i]=1;
				flag|=!SG[1][x]|!SG[0][x];
			}
			for(int k:v[x])cnt2[k]-=cnt2[x];
		}
		if(!flag)SG[cnt[i]%2][i]=1;
	}
	for(int i=1;i<=n;i++)
		if(SG[0][a[i]])cout<<"Aoki\n";
		else cout<<"Takahashi\n";
}