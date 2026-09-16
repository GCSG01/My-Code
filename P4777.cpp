#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N=2e5+5;
int a[N],b[N];
inline void rd(int &x){
    long long tmp;cin>>tmp,x=tmp;
}
inline void print(int sum){
	if(sum>9)print(sum/10);
	putchar(sum%10+'0');
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
void exgcd(int a,int b,int &x,int &y){
    if(!b)return x=1,y=0,void();
    exgcd(b,a%b,y,x),y-=a/b*x;
}
int get(int a,int b,int c){
	int x,y,d=gcd(a,b);
	exgcd(a,b,x,y);
	x=x*c/d,y=y*c/d;
	return x;
}
signed main(){
	int n;rd(n);
	for(int i=1;i<=n;i++)
		rd(b[i]),rd(a[i]);
	for(int i=2;i<=n;i++){
		int x=get(b[i-1],-b[i],a[i]-a[i-1]),d=gcd(b[i-1],b[i]);
		d=b[i-1]*b[i]/d;
		a[i]=((a[i-1]+x*b[i-1]%d)%d+d)%d,b[i]=d;
	}
	print(a[n]);
	return 0;
}