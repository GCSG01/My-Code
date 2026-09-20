#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=70;
int n,p[N],a[N];
void add(int x){
	for(int i=62;i>=0;i--){
		if(!(x>>i))continue;
		if(!p[i]){
			p[i]=x;break;
		}
		x^=p[i];
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],add(a[i]);
	int ans=0;
	for(int i=62;i>=0;i--)
		if((ans^p[i])>=ans)ans^=p[i];
	cout<<ans;
}