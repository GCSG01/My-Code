#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++)cout<<i<<" ";
	for(int i=n+m+1;i>=n+1;i--)cout<<i<<" ";
    return 0;
}