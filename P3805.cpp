#include<bits/stdc++.h>
using namespace std;
const int N=4e7+5;
char c[N];
int p[N];
int n,ans=0;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	char ch;
	c[++n]='#',c[++n]='|';
	while(cin>>ch)c[++n]=ch,c[++n]='|';
	c[++n]='@';
	int mx=0,mid=0;
	for(int i=2;i<n;i++){
		if(i<=mx)p[i]=min(p[mid*2-i],mx-i+1);
		else p[i]=1;
		while(c[i-p[i]]==c[i+p[i]])p[i]++;
		if(i+p[i]>mx)mx=i+p[i]-1,mid=i;
		ans=max(ans,p[i]-1);
	}
	cout<<ans;
}