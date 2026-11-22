#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
string S,s[N];
int n;
bool check(string x,string y){
	int pos=0;
	for(auto c:y)
		if(pos<x.size()&&c==x[pos])
			pos++;
	return pos>=x.size();
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>S;
	for(int i=1;i<=n;i++)cin>>s[i];
	sort(s+1,s+n+1,[](string x,string y){
		return x.size()<y.size();
	});
	for(int i=1;i<=n;i++)
		if(!check(s[i],S))
			cout<<"impossible",exit(0);
	queue<int>a[2],b;
	for(int i=1;i<=n;i++){
		int f0=0,f1=0;
		if(a[0].empty()||check(s[a[0].back()],s[i]))f0=1;
		if(a[1].empty()||check(s[a[1].back()],s[i]))f1=1;
		if(!f0&&!f1)cout<<"impossible",exit(0);
		if(f0&&f1&&(b.empty()||check(s[b.back()],s[i])))
			b.push(i);
		else if(f0&&f1){
			a[0].push(i);
			while(!b.empty())
				a[1].push(b.front()),b.pop();
		}
		else{
			a[f0?0:1].push(i);
			while(!b.empty())
				a[f0?1:0].push(b.front()),b.pop();
		}
	}
	while(!b.empty())
		a[0].push(b.front()),b.pop();
	cout<<a[0].size()<<" "<<a[1].size()<<"\n";
	while(!a[0].empty())
		cout<<s[a[0].front()]<<"\n",a[0].pop();
	while(!a[1].empty())
		cout<<s[a[1].front()]<<"\n",a[1].pop();
}