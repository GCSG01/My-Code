#include<bits/stdc++.h>
#define int long long
#define pqpair priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>
using namespace std;
const int N=1e6+5,inf=1e18;
int n,k,l,a[N],b[N];
bitset<N>visa,visb;
priority_queue<pair<int,int>>compla,complb,chospair,bothmin;
pqpair qa,qb;
void upd(int i){
	if(!visa[i]&&!visb[i])chospair.push({a[i]+b[i],i});
	else if(visa[i]&&!visb[i])compla.push({b[i],i}),qa.push({a[i],i});
	else if(visb[i]&&!visa[i])complb.push({a[i],i}),qb.push({b[i],i});
	else bothmin.push({-a[i]-b[i],i});
}
void clean(){
	while(!compla.empty()){
		int i=compla.top().second;
		if(visa[i]&&!visb[i])break;
		compla.pop();
	}
	while(!complb.empty()){
		int i=complb.top().second;
		if(visb[i]&&!visa[i])break;
		complb.pop();
	}
	while(!chospair.empty()){
		int i=chospair.top().second;
		if(!visa[i]&&!visb[i])break;
		chospair.pop();
	}
	while(!bothmin.empty()){
		int i=bothmin.top().second;
		if(visa[i]&&visb[i])break;
		bothmin.pop();
	}
	while(!qa.empty()&&(!visa[qa.top().second]||visb[qa.top().second]))qa.pop();
	while(!qb.empty()&&(!visb[qb.top().second]||visa[qb.top().second]))qb.pop();
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>k>>l;
		while(!qa.empty())qa.pop();
		while(!qb.empty())qb.pop();
		while(!compla.empty())compla.pop();
		while(!complb.empty())complb.pop();
		while(!chospair.empty())chospair.pop();
		while(!bothmin.empty())bothmin.pop();
		for(int i=1;i<=n;i++)visa[i]=visb[i]=0;
		int ans=0,nowl=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(qa.size()<k)qa.push({a[i],i}),visa[i]=1,ans+=a[i];
			else if(qa.top().first<a[i])
				visa[qa.top().second]=0,visa[i]=1,
				ans+=a[i]-qa.top().first,
				qa.pop(),qa.push({a[i],i});
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(qb.size()<k)qb.push({b[i],i}),visb[i]=1,ans+=b[i];
			else if(qb.top().first<b[i])
				visb[qb.top().second]=0,visb[i]=1,
				ans+=b[i]-qb.top().first,
				qb.pop(),qb.push({b[i],i});
		}
		while(!qa.empty())qa.pop();
		while(!qb.empty())qb.pop();
		for(int i=1;i<=n;i++){
			if(visa[i]&&visb[i])nowl++;
			upd(i);
		}
		while(nowl<l){
			clean();
			int sum1=-inf,sum2=-inf,sum3=-inf,sum4=-inf;
			if(!bothmin.empty()&&!compla.empty()&&!complb.empty())
				sum1=bothmin.top().first+compla.top().first+complb.top().first;
			if(!qa.empty()&&!complb.empty())sum2=-qa.top().first+complb.top().first;
			if(!qb.empty()&&!compla.empty())sum3=-qb.top().first+compla.top().first;
			if(!chospair.empty()&&!qa.empty()&&!qb.empty())
				sum4=chospair.top().first-qa.top().first-qb.top().first;
			int mx=max({sum1,sum2,sum3,sum4});
			ans+=mx;
			nowl++;
			if(sum1==mx){
				int t=bothmin.top().second;
				int x=compla.top().second;
				int y=complb.top().second;
				visa[t]=visb[t]=0;
				visb[x]=1;
				visa[y]=1;
				upd(t),upd(x),upd(y);
			}
			else if(sum2==mx){
				int x=qa.top().second;
				int y=complb.top().second;
				visa[x]=0;
				visa[y]=1;
				upd(x),upd(y);
			}
			else if(sum3==mx){
				int x=qb.top().second;
				int y=compla.top().second;
				visb[x]=0;
				visb[y]=1;
				upd(x),upd(y);
			}
			else{
				int x=qa.top().second;
				int y=qb.top().second;
				int z=chospair.top().second;
				visa[x]=visb[y]=0;
				visa[z]=visb[z]=1;
				upd(x),upd(y),upd(z);
			}
		}
		cout<<ans<<"\n";
	}
}
