#include<bits/stdc++.h>
#define uint unsigned int
using namespace std;
const int N=2e7+5;
uint seed;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
uint n,a[N];
bitset<N>vis;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>seed;
	for(int i=1;i<=n;i++)a[i]=getnext();
	vis[1]=1;
	for(int i=2;i<=n;i++)
        if(!vis[i])
            for(int j=1,k=i;k<=n;j++,k+=i)
                a[k]+=a[j],vis[k]=1;
    uint ans=0;
	for(int i=1;i<=n;i++)ans^=a[i];
	cout<<ans;
	return 0;
}