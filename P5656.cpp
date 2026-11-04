#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
void exgcd(int a,int b,int &x,int &y){
	if(!b)return x=1,y=0,void();
	exgcd(b,a%b,y,x),y-=a/b*x;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		int a,b,c,d;cin>>a>>b>>c;
		if(c%(d=gcd(a,b))){
			cout<<"-1\n";continue;
		}
		int x,y;
		exgcd(a,b,x,y);
		x=x*c/d,y=y*c/d;
		int xx=b/d;
		int yy=a/d;
		int k=ceil((1-x)*1.0/xx);
		x+=xx*k,y-=yy*k;
		if(y<=0)
			cout<<x<<" "<<y+(yy-y)/yy*yy<<"\n";
		else y--,cout<<y/yy+1<<" "<<x<<" "<<y%yy+1<<" "<<x+y/yy*xx<<" "<<y+1<<"\n";
	}
}