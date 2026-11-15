#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,k;
int pre[N];
int a[N],tr[N];
inline int lowbit(int x){return x&-x;}
inline void update(int x,int k){
	while(x<=n)tr[x]+=k,x+=lowbit(x);
}
inline int query(int x,int s=0){
	while(x)s+=tr[x],x-=lowbit(x);
	return s;
}
priority_queue<pair<int,int>>q;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		pre[i]=i-1-query(a[i]),update(a[i],1);//求逆序对
	int ans=0,pos=k;
	for(int i=1;i<=k;i++){
		if(pre[i])ans++;
		q.push({a[i],i});//第一个k-lentgth前缀
	}
	ans=-max(0ll,ans-1);
	for(int i=2;i<=n;i++){
		int flag=0;
		for(int j=pos+1;j<=pos+k-1&&j<=n;j++)
			if(q.top().first>a[j]){//动态维护
				q.pop(),q.push({a[j],j});
				if(pre[j]>(i-1)*(k-1))flag++;//计数
			}
		ans-=max(0ll,flag-1),pos+=k-1;
	}
	for(int i=1;i<=n;i++)ans+=ceil(pre[i]*1.0/(k-1));
	cout<<ans<<"\n";//AT 怎么还判行末换行呢
}
/*
"特別なことはないけど、君がいると十分です",
"今でもあなたは私の光",
"君ってさ、知らないうちに私の毎日になってたよ",
"君と話すと、なんか毎日がちょっと楽しくなるんだ",
"今日はなんでもない日。でも、ちょっとだけいい日",
*/