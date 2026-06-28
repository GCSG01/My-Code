#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n;
int a[N];
int t[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)t[i]=0;
        for(int i=1;i<=n;i++)cin>>a[i],t[a[i]]++;
        int mx=0,s=0;
        for(int i=1;i<=n;i++)
            if(t[i]>mx)mx=t[i],s=1;
            else if(t[i]==mx)s++;
        cout<<(n-mx-s+1)/(mx-1)<<"\n";
    }
    return 0;
}