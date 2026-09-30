#include<bits/stdc++.h>
using namespace std;
const int N=4e5+9;
struct node{
	int x,y;
}a[N],b[N];
int n,m,ans;
multiset<int>s;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m,ans=n;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
	for(int i=1;i<=m;i++)cin>>b[i].x>>b[i].y;
    auto cmp=[](node A,node B){return A.x<B.x;};
	sort(a+1,a+n+1,cmp),sort(b+1,b+m+1,cmp);
	for(int i=1,j=1;i<=m;i++){
		while(j<=n&&a[j].x<=b[i].x)s.insert(a[j++].y);
		while(!s.empty()&&*s.begin()<b[i].x)s.erase(s.begin());
		while(!s.empty()&&s.size()>b[i].y)s.erase(--s.end()),ans--;
	}
	cout<<ans;
}