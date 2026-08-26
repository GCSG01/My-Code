#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,inf=2e18;
struct cow{
	int len,d[20],v;
}p[N];
struct node{
	int v,x,y;
};
int n,k,ans;
priority_queue<node>q;
bool operator<(node u,node v){return u.v>v.v;}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
    for(int i=1;i<=n;i++){
		cin>>p[i].len;
		for(int j=1;j<=p[i].len;j++)
            cin>>p[i].d[j];
		p[i].d[p[i].len+1]=inf;
		sort(p[i].d+1,p[i].d+p[i].len+1,[](int A,int B){return A<B;});
		p[i].v=p[i].d[2]-p[i].d[1],ans+=p[i].d[1];
	}
	sort(p+1,p+n+1,[](cow A,cow B){return A.v<B.v;});
	q.push({ans-p[1].d[1]+p[1].d[2],1,2});
	for(int i=1;i<k;i++){
		node u=q.top();q.pop();
        auto [v,x,y]=u;
		ans+=v;
		q.push({v-p[x].d[y]+p[x].d[y+1],x,y+1});
		if(x!=n)
			q.push({v-p[x+1].d[1]+p[x+1].d[2],x+1,2});
		if(x!=n&&y==2)
			q.push({v-p[x+1].d[1]+p[x+1].d[2]-p[x].d[2]+p[x].d[1],x+1,2});
	}
    cout<<ans;
	return 0;
}