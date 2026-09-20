#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int n,ans,p[N];
struct node{
	int x,y;
}a[N];
void add(int x){
	for(int i=62;i>=0;i--){
		if(!((a[x].x>>i)&1))continue;
		if(!p[i]){
			p[i]=a[x].x,ans+=a[x].y;
			break;
		}
		a[x].x^=p[i];
	}
	return ;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,[](node A,node B){
        return A.y>B.y;
    });
	for(int i=1;i<=n;i++)add(i);
	cout<<ans;
}