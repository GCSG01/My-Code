#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=(1<<20)+5;
int n,m;
double p[N];
inline double get(int S){
    return 1/(1-p[(m-1)^S]);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n,m=(1<<n);
    for(int i=0;i<m;i++)cin>>p[i];
    for(int k=1;k<m;k<<=1)
		for(int s=0;s<m;s+=k<<1)
			for(int i=s;i<s+k;i++)
                p[i+k]+=p[i];
    double ans=0;
    for(int S=1;S<m;S++){
        if(1-p[(m-1)^S]<1e-6)
            return cout<<"INF",0;
        if(__builtin_popcount(S)&1)ans+=get(S);
        else ans-=get(S);
    }
    printf("%.6lf",ans);
}