#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int n;
struct node{
	int x,y;
}p[N];
bool operator<(const node &A,const node &B){
	return A.y==B.y?A.x<B.x:A.y<B.y;
}
set<node>st;
int sqr(int x){return x*x;}
int dis(node A,node B){
	return sqr(A.x-B.x)+sqr(A.y-B.y);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>p[i].x>>p[i].y;
	sort(p+1,p+n+1,[](node A,node B){return A.x==B.x?A.y<B.y:A.x<B.x;});
	int ans=dis(p[1],p[2]);
	for(int i=1,j=1;i<=n;i++){
		while(ans<=sqr(p[i].x-p[j].x))		
			st.erase(p[j++]);
		auto pos=st.lower_bound(p[i]),k=pos;
		while(k!=st.end()&&sqr(k->y-p[i].y)<ans)
			ans=min(ans,dis(*k,p[i])),k++;
		if(pos!=st.begin())
			for(k=--pos;sqr(k->y-p[i].y)<ans;k--){
				ans=min(ans,dis(*k,p[i]));
				if(k==st.begin())break;
			}
		st.insert(p[i]);
	} 
	cout<<ans;
}