#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int n,m;
int a[N][N],b[N][N];
int dis[N*3],cnt[N*3],f[N*3];
struct node{
    int v,w;
};
vector<node>e[N*3];
void add(int x,int y,int w){
    e[x].push_back({y,w});
    return ;
}
int spfa(){
    memset(dis,0x3f,sizeof dis);
    memset(cnt,0,sizeof cnt);
    memset(f,0,sizeof f);
	dis[1]=0,f[1]=1;
	queue<int>q;q.push(1);
	while(!q.empty()){
		int u=q.front();q.pop();
		f[u]=0;
		for(auto i:e[u]){
			int v=i.v,w=i.w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w,cnt[v]=cnt[u]+1;
				if(cnt[v]>=n+m)return -1;
				if(!f[v])q.push(v),f[v]=1;
			}
		}
	}
	return 0;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n+m;i++)
            e[i].clear();
        for(int i=1;i<n;i++)
            for(int j=1;j<m;j++)
                cin>>b[i][j];
        for(int i=1;i<=n;i++)a[i][m]=0;
        for(int i=1;i<=m;i++)a[n][i]=0;
        for(int i=n-1;i>=1;i--)
            for(int j=m-1;j>=1;j--)
                a[i][j]=b[i][j]-a[i+1][j]-a[i][j+1]-a[i+1][j+1];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                int mx=1000000-a[i][j];
                if((i+j)&1)add(j+n,i,a[i][j]),add(i,j+n,mx);
                else add(j+n,i,mx),add(i,j+n,a[i][j]);
            }
        if(spfa()==-1){
            cout<<"NO\n";
            continue;
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if((i+j)&1)a[i][j]-=dis[i]-dis[j+n];
                else a[i][j]+=dis[i]-dis[j+n];
        cout<<"YES\n";
        for(int i=1;i<=n;i++,cout<<"\n")
            for(int j=1;j<=m;j++)
                cout<<a[i][j]<<" ";
    }
    return 0;
}