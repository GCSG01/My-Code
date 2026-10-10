#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m,a,b;cin>>n>>m>>a>>b;
        if(n>m)swap(n,m);
        if(a>b)swap(a,b);
        if(n==a&&b==m)cout<<"An-An\n";
        else if(a!=1)cout<<"Miria\n";
        else if(b==1)cout<<"An-An\n";
        else if(m==b)cout<<"An-An\n";
        else if(n==2&&b==2)cout<<"An-An\n";
        else if(n==b&&m==b+1)cout<<"An-An\n";
        else cout<<"Miria\n";
    }
}