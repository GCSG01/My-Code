#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int n,m,k;
int dp[N][N],mil[N][N];
struct node{
	int c,l,r;
}a[N][N];
char ans[N*3];
string s;
inline void dfs(int l,int r){
	if(r<l)return;
	if(l==r){
		if(s[l]=='?')ans[++m]='a';
		else if(s[l]!='*')ans[++m]=s[l]; 
		return;
	}
	if(a[l][r].c==1){
		if(s[l]=='*'&&s[r]=='*')
			dfs(l+1,r-1);
		else{
			char c='a';
			if(s[l]!='?')c=s[l];
			if(s[r]!='?')c=s[r];
			if(c=='*')c='a';
			ans[++m]=c,dfs(l+1,r-1),ans[++m]=c;
		}
		return ;
	}
	if(a[l][r].c==2){
		for(int i=r;i>=a[l][r].r+1;i--)
			if(s[i]=='?')
				ans[++m]='a';
			else if(s[i]!='*')
				ans[++m]=s[i];
		dfs(a[l][r].l,a[l][r].r);
		for(int i=a[l][r].r+1;i<=r;i++)
			if(s[i]=='?')
				ans[++m]='a';
			else if(s[i]!='*')
				ans[++m]=s[i];
		return ;
	}
	for(int i=l;i<=a[l][r].l-1;i++)
		if(s[i]=='?')
			ans[++m]='a';
		else if(s[i]!='*')
			ans[++m]=s[i];
	dfs(a[l][r].l,a[l][r].r);
	for(int i=a[l][r].l-1;i>=l;i--)
		if(s[i]=='?')
			ans[++m]='a';
		else if(s[i]!='*')
			ans[++m]=s[i];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>s,n=s.size(),s=" "+s;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			mil[i][j]=mil[i][j-1]+(s[j]!='*');
	int l=n/2;
	for(int i=1;i<=l;i++){
		if(s[i]=='*')
			break;
		if(s[n-i+1]=='*')
			break;
		if(s[i]!='?'&&s[n-i+1]!='?'&&s[i]!=s[n-i+1])
			return cout<<-1,0;
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		if(s[i]=='*')
			dp[i][i]=0;
		else dp[i][i]=1;
		dp[i][i-1]=0;
	}
	int inf=dp[0][0];
	for(int l=2;l<=n;l++)
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			if((s[i]==s[j]||s[i]=='?'||s[j]=='?')&&dp[i+1][j-1]>=0){
				int cnt=dp[i+1][j-1];
				if(s[i]!='*'||s[j]!='*')cnt+=2;
				if(cnt<dp[i][j])
					dp[i][j]=cnt,a[i][j]={1,i+1,j-1};
			}
			if(s[i]=='*')
				for(int k=i+1;k<=j+1;k++)
				if(dp[i+1][k-1]>=0){
					int cnt=dp[i+1][k-1]+2*mil[k][j];
					if(cnt<dp[i][j])
						dp[i][j]=cnt,a[i][j]={2,i+1,k-1};
				}
			if(s[j]=='*')
				for(int k=j-1;k>=i-1;k--)
					if(dp[k+1][j-1]>=0){
						int cnt=dp[k+1][j-1]+2*mil[i][k];
						if(cnt<dp[i][j])
							dp[i][j]=cnt,a[i][j]={3,k+1,j-1};
					}
			if(dp[i][j]==inf)
				dp[i][j]=-1;
		}
	m=0,dfs(1,n);
	for(int i=1;i<=m;i++)
		cout<<ans[i];
}