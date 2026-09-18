#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int m=1;
    int n;cin>>n;
    while(m<=n)m*=2;
    cout<<(((-n*n)-(n%2))%m+m)%m;
}