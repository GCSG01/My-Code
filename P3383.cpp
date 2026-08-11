#include<bits/stdc++.h>
using namespace std;
const int N=1e8+5;
bitset<N>f;
int p[N],a[N];
#ifdef ONLINE_JUDGE
    #define getchar getchar_unlocked
#endif
inline void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
}
inline void print(int x){
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}
int main(){
    std::ios::sync_with_stdio(0);
	register int cnt=0,n,m,i,j;
    rd(n),rd(m),f[1]=1;
	for(i=1;i<=m;i++)rd(a[i]);
    for(i=2;i<=n;i++){
		if(!f[i])p[++cnt]=i;
        for(j=1;j<=cnt&&i*p[j]<=n;j++){
            f[p[j]*i]=1;
            if(i%p[j]==0)break;
        }
    }
	for(i=1;i<=m;i++)print(p[a[i]]),puts("");
}