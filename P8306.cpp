#include<bits/stdc++.h>
using namespace std;
const int N=3e6+5;
int trie[N][62],tot;
int sum[N];
inline int get(char c){
	if(c>='A'&&c<='Z')return c-'A';
	if(c>='a'&&c<='z')return c-'a'+26;
	return c-'0'+52;
}
void insert(string s){
	int now=0;
	for(int i=0;i<s.size();i++){
		int c=get(s[i]);
		if(!trie[now][c])trie[now][c]=++tot;
		now=trie[now][c],sum[now]++;
	}
}
int query(string t){
	int now=0;
	for(int i=0;i<t.size();i++){
		now=trie[now][get(t[i])];
		if(!now)return 0;
	}
	return sum[now];
}
void solve(){
	for(int i=0;i<=tot;i++)sum[i]=0;
	for(int i=0;i<=tot;i++)
		for(int j=0;j<62;j++)
			trie[i][j]=0;
	tot=0;
	int n,q;cin>>n>>q;
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		insert(s);
	}
	while(q--){
		string t;cin>>t;
		cout<<query(t)<<"\n";
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--)solve();
}