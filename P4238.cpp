#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
int n;
struct complx{
    double x,y;
    complx operator+(const complx &B)const{return {x+B.x,y+B.y};}
}a[N];

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x;
    int lim=1;
    while(lim<n)lim<<=1;
    return 0;
}