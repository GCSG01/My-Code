#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int N=5e2+5,M=1.25e5+5;
int n,m,deg[N];
pair<int,int>e[M];
vector<int>g[N];
double a[N][N],b[N],x[N],f[M];
inline void add(int x,int y){
    g[x].push_back(y),g[y].push_back(x),deg[x]++,deg[y]++;
}
void gauss(int n){
	for(int i=1;i<=n;i++){
		int now=i;
		for(int k=i+1;k<=n;k++)
            if(fabs(a[k][i])>fabs(a[now][i]))
                now=k;
		if(i!=now)
            swap(a[i],a[now]),swap(b[i],b[now]);
		for(int k=i+1;k<=n;k++){
            double xx=a[k][i],yy=a[i][i];
			b[k]-=xx*b[i]/yy;
			for(int j=i;j<=n;j++)
                a[k][j]-=xx*a[i][j]/yy;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++)
            b[i]-=x[j]*a[i][j];
		x[i]=b[i]/a[i][i];
	}
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>e[i].fi>>e[i].se,add(e[i].fi,e[i].se);
    for(int i=1;i<n;i++){
        a[i][i]=1.0;
		for(int y:g[i])
			if(y!=n)a[i][y]=-1.0/deg[y];
    }
    b[1]=1;
    gauss(n-1);
	for(int i=1;i<=m;i++){
        auto [u,v]=e[i];
        if(u!=n)f[i]+=x[u]/deg[u];
        if(v!=n)f[i]+=x[v]/deg[v];
	}
    sort(f+1,f+m+1);
    double ans=0;
    for(int i=1;i<=m;i++)
        ans+=f[i]*(m-i+1);
    printf("%.3lf",ans);
}