#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=998244353;
int n,pw[N];
int trie[N][2],tot=0;
int siz[N],f[N],vis[N];
stack<int>st;
#define ls(p) trie[(p)][0]
#define rs(p) trie[(p)][1]
void insert(string s){
	int now=0;
	for(auto i:s){
		int c=i-'A';
		if(!trie[now][c])trie[now][c]=++tot;
		if(!trie[now][c^1])trie[now][c^1]=++tot;
		st.push(now),now=trie[now][c];
	}
	vis[now]=1,st.push(now);
	while(!st.empty()){
		int p=st.top();st.pop();
		if(!ls(p)||!rs(p))siz[p]=f[p]=vis[p];
		else{
			siz[p]=siz[ls(p)]+siz[rs(p)]+vis[p],siz[p]%=mod;
			f[p]=(f[ls(p)]*f[rs(p)])%mod;
			if(vis[p])f[p]+=pw[siz[p]-1],f[p]%=mod;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n,pw[0]=1;
	for(int i=1;i<=N-5;i++)pw[i]=pw[i-1]*2%mod;
	string s;
	for(int i=1;i<=n;i++)
		cin>>s,insert(s),cout<<f[0]<<"\n";
}