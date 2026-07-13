#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,mod=1e9;
int n,m;
char mp[15][15];
int id[15][15],tot;
int a[N][N];
void add(int x,int y){
    a[x][x]++,a[y][y]++,
    a[x][y]--,a[y][x]--;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='.')
                id[i][j]=++tot;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='.'&&mp[i+1][j]=='.')add(id[i][j],id[i+1][j]);
            if(mp[i][j]=='.'&&mp[i][j+1]=='.')add(id[i][j],id[i][j+1]);
        }
    tot--;
    int ans=1;
	for(int i=1;i<tot;i++)
		for(int j=i+1;j<=tot;j++)
			while(a[j][i]){
				int l=a[i][i]/a[j][i];
				for(int k=1;k<=tot;k++)
					a[i][k]=(a[i][k]-a[j][k]*l%mod+mod)%mod;
				for(int k=1;k<=tot;k++)
                    swap(a[i][k],a[j][k]);
				ans*=-1;
			}
	for(int i=1;i<=tot;i++)
        ans=(ans*a[i][i]+mod)%mod;
    cout<<ans;
    return 0;
}