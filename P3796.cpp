#include<bits/stdc++.h>
using namespace std;
const int N=155;
int n;
string s[N];
string t;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>n){
        if(!n)break;
        init();
        for(int i=1;i<=n;i++)cin>>s[i],ins(s[i]);
        cin>>t;
    }
    return 0;
}