#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
int n,c;
int st[N],a[N],b[N],top,cnt1,cnt2;
char mp[N],rev[N];
bitset<N>vis;
void solve(){
	string s,t;cin>>n>>c>>t,s=t=" "+t,cnt1=cnt2=top=0;
	mp['U']='U',mp['D']='D',mp['L']='L',mp['R']='R';
	if(c==2||c==3)swap(mp['L'],mp['R']);
	if(c==3||c==4)swap(mp['D'],mp['U']);
	if(n&1)return cout<<"N0\n",void();
	cout<<"YE5\n";
	for(int i=1;i<=n;i++)s[i]=mp[t[i]],vis[i]=1;
	for(int i=1;i<=n;i++)
		if(s[i]=='U')st[++top]=i;
		else if(s[i]=='D'){
			if(top)top--;
			else vis[i]=0;
		}
	while(top)vis[st[top--]]=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='R')st[++top]=i;
		else if(s[i]=='L'){
			if(top)top--;
			else vis[i]=0;
		}
	while(top)vis[st[top--]]=0;
	for(int i=1;i<=n;i++)
		if(vis[i]);
		else if(s[i]=='U'||s[i]=='R')
			a[++cnt1]=i;
		else b[++cnt2]=i;
	int ans=(cnt1+cnt2)/2,p=1;
	if(cnt1&1){
		if(a[1]<b[cnt2])s[b[cnt2]]=rev[s[a[1]]];
		else{
			char x=s[b[cnt2]];
			s[b[cnt2]]=rev[x],s[a[1]]=x;
			ans++;
		}
		p++,cnt1--,cnt2--;
	}
	cout<<ans<<"\n";
	for(int i=p;i<=cnt1;i+=2)s[a[i+1]]=rev[s[a[i]]];
	for(int i=1;i<=cnt2;i+=2)s[b[i]]=rev[s[b[i+1]]];
	for(int i=1;i<=n;i++)cout<<mp[s[i]];
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	freopen("retrace.in","r",stdin);
	freopen("retrace.out","w",stdout);
	rev['U']='D',rev['D']='U',rev['L']='R',rev['R']='L';
	int T;cin>>T>>c;
	while(T--) solve();
}