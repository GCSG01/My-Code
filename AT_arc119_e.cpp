#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=3e5+5;
int a[N],n;
struct node{
	int l,r;
	bool op;
	int idx;
}l[N];
node s1[N],s2[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
    int Ans=0,cnt1=0,cnt2=0;
	for(int i=1;i<n;i++){
        l[i]={min(a[i],a[i+1]),max(a[i],a[i+1]),(a[i]>=a[i+1]),l[i].idx=i};
        Ans+=l[i].r-l[i].l;
        if(l[i].op)s1[++cnt1]=l[i];
        else s2[++cnt2]=l[i];
	}
	sort(s1+1,s1+cnt1+1,[](node A,node B){return A.l<B.l;});
	sort(s2+1,s2+cnt2+1,[](node A,node B){return A.l<B.l;});
	int mx=0,ans=0;
	for(int i=1;i<=cnt2;i++)
		ans=max(ans,min(mx,s2[i].r)-s2[i].l),mx=max(mx,s2[i].r);
	mx=0;
	for(int i=1;i<=cnt1;i++)
		ans=max(ans,min(mx,s1[i].r)-s1[i].l),mx=max(mx,s1[i].r);
	int sum=Ans;
	for(int i=2;i<n;i++)
		sum=min(sum,Ans-llabs(a[i+1]-a[i])+llabs(a[1]-a[i+1]));
	for(int i=2;i<n;i++)
		sum=min(sum,Ans-llabs(a[i]-a[i-1])+llabs(a[n]-a[i-1]));
	cout<<min(sum,Ans-2*ans)<<'\n';
}