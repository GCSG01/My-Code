#include<bits/stdc++.h>
using namespace std;
const int N=3e6+5;
int t,at,bt;
char a[N],b[N],s[N];
string op;
inline int read(){
	int x=0,sgn=0; char s=getchar();
	while(!isdigit(s))sgn|=s=='-',s=getchar();
	while(isdigit(s))x=x*10+s-'0',s=getchar();
	return sgn?-x:x;
}
int main(){
    // ios::sync_with_stdio(0);cin.tie(0);
	cin>>t;
	for(int i=1,x;i<=t;i++){
		cin>>op;
		if(op.size()<3)cin>>op;
		if(op[0]=='M'){
			x=read();
			while(at>x)b[++bt]=a[at--];
			while(at<x)a[++at]=b[bt--];
		}
		if(op[0]=='I'){
			int len=0;cin>>x;
			while(len<x){
				s[++len]=getchar();
				if(s[len]<32||s[len]>126)len--;
			}
			for(int j=x;j;j--)b[++bt]=s[j];
		}
		if(op[0]=='D'){
            cin>>x;
            while(x--)
                bt--;
        }
		if(op[0]=='G'){
			int pos=bt;cin>>x;
			while(x--)cout<<b[pos--];
			puts("");
		}
		if(op[0]=='P')
            b[++bt]=a[at--];
		if(op[0]=='N')
            a[++at]=b[bt--];
	}
	return 0;
}