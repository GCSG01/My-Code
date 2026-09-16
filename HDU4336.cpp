#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=22;
double p[N];
int n;
double get(int S){
    double sum=0;
    for(int i=1;i<=n;i++)
        if((1<<(i-1))&S)sum+=p[i];
    if(!sum)return 0;
    return 1/sum;
}
signed main(){
    // ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>n){
        for(int i=1;i<=n;i++)cin>>p[i];
        double ans=0;
        for(int S=1;S<(1<<n);S++)
            if(__builtin_popcount(S)&1)ans+=get(S);
            else ans-=get(S);
        printf("%.6lf\n",ans);
    }
}