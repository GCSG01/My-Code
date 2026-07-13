#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
const int N=305,mod=1e9+7;
int m[N];
pair<int,int>bg[N][N];
int a[N][N];
int n; 
int det(){
    int ans=1;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			while(a[j][i]){
				int l=a[i][i]/a[j][i];
				for(int k=1;k<=n;k++)
					a[i][k]=(a[i][k]-a[j][k]*l%mod+mod)%mod;
				for(int k=1;k<=n;k++)
                    swap(a[i][k],a[j][k]);
				ans*=-1;
			}
	for(int i=1;i<=n;i++)
        ans=(ans*a[i][i]+mod)%mod;
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n,n--;
    for(int i=1;i<=n;i++){
        cin>>m[i];
        for(int j=1;j<=m[i];j++)
            cin>>bg[i][j].fi>>bg[i][j].se;
    }
    int ans=0;
    for(int i=1;i<(1<<n);i++){
        memset(a,0,sizeof a);
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(!(i&(1<<(j-1))))continue;
            cnt++;
            for(int k=1;k<=m[j];k++){
                int u=bg[j][k].fi,v=bg[j][k].se;
                a[u][u]++,a[v][v]++,a[u][v]--,a[v][u]--;
            }
        }
        ans+=det()*(((n-cnt)&1)?-1:1);
        while(ans<0)ans+=mod;
        ans%=mod;
    }
    cout<<ans;
    return 0;
}