#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
inline void rd(int &x){
	char c=getchar_unlocked();x=0;
	bool f=0;
	while(c<'0'||c>'9')f|=c=='-',c=getchar_unlocked();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar_unlocked();
	f?x=-x:0;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;rd(n);
	int x,sum=0;
	while(n--)rd(x),sum+=x;
	cout<<sum;
}