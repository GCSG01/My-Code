#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e5+5;
struct node{
	int val,tp;
	friend bool operator<(node a,node b){
        return a.val==b.val?a.tp>b.tp:a.val>b.val;
    }
};
priority_queue<node>pq;
int n,k;
int a[N];
int b[N];
int get(int x){
    int cnt=0;
	for(int i=1;i<=n;i++){
		pq.push({a[i],1});
        node now=pq.top();
        int s=b[i]+now.val+x;
		if(s<0)
            cnt+=now.tp,pq.pop(),pq.push({-x-b[i],0});
	}
    while(!pq.empty())pq.pop();
    return cnt;
}
#ifdef ONLINE_JUDGE
    #define getchar getchar_unlocked
#endif
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(k);
    for(int i=1;i<=n;i++)rd(a[i]);
    for(int i=1;i<=n;i++)rd(b[i]);
	int l=-(1ll<<31),r=0;
	while(l<r){
		int mid=(l+r-1)/2;
        if(get(mid)<=k)r=mid;
        else l=mid+1;
	}
    int sum=0;
	for(int i=1;i<=n;i++){
		pq.push({a[i],1});
        node now=pq.top();
        int s=b[i]+now.val+l;
		if(s<0)
            sum+=s,pq.pop(),pq.push({-l-b[i],0});
	}
    
    cout<<sum-l*k;
}