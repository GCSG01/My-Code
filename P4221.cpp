#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=22,mod=998244353;
int n,m,p,lim;
int w[N],W[1<<N],fa[N],cont[1<<N],in[N],ok[1<<N],g[N][1<<N],inv[1<<N],f[N][1<<N];
pair<int,int>e[N*N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        y>>=1,x*=x,x%=mod;
    }
    return s;
}
void fwt(int *a,int opt){
	for(int i=2;i<=lim;i<<=1)
        for(int p=i>>1,j=0;j+i<=lim;j+=i)
            for(int k=j;k<j+p;k++)
                a[p+k]=(a[p+k]+opt*a[k]+mod)%mod;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>p;
    for(int i=1;i<=m;i++)
        cin>>e[i].first>>e[i].second;
    for(int i=1;i<=n;i++)cin>>w[i];
    lim=1<<n;
    for(int s=0;s<lim;s++){
        int cnt=0;
		for(int i=1;i<=n;i++){
			if((1<<(i-1))&s)W[s]+=w[i],cnt++;
			in[i]=0,fa[i]=i;
		}
		cont[s]=cnt;
		for(int i=1;i<=m;i++){
			if(((1<<(e[i].first-1))&s)&&((1<<(e[i].second-1))&s)){
				if(find(e[i].first)!=find(e[i].second))
                    merge(e[i].first,e[i].second),cnt--;
				in[e[i].first]++,in[e[i].second]++;
			}
		}
		if(cnt!=1)ok[s]=1;
		cnt=0;
		for(int i=1;i<=n;i++)cnt+=(in[i]&1);
		if(cnt)ok[s]=1;
		if(ok[s])
            g[cont[s]][s]=qpow(W[s],p);
		inv[s]=qpow(qpow(W[s],mod-2),p);
    }
    for(int i=0;i<=n;i++)fwt(g[i],1);
    f[0][0]=1,fwt(f[0],1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++)
			for(int k=0;k<lim;k++)
				(f[i][k]+=f[j][k]*g[i-j][k]%mod)%=mod;
		fwt(f[i],-1);
		for(int j=0;j<lim;j++)
			f[i][j]=cont[j]==i?f[i][j]*inv[j]%mod:0;
		if(i!=n)fwt(f[i],1);
	}
	cout<<f[n][lim-1];
    return 0;
}