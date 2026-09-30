#include<bits/stdc++.h>
using namespace std;
int n,m,q;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>q;
    vector<bitset<128>>a(m+2),b(m+2),c(m+2);
    for(int i=0;i<q;i++){
        string s;cin>>s;
        for(int j=0;j<m;j++)
            b[j+1][i]=s[j]-'0';
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++)
            c[j]=~(a[j]^b[j-1]^b[j]^b[j+1]);
        swap(a,b),swap(b,c);
    }
    for(int i=0;i<q;i++){
        string ans(m,'0');
        for(int j=0;j<m;j++)
            if((b[j][i]^b[j+1][i]^b[j+2][i]^a[j+1][i])==1)
                ans[j]='1';
        cout<<ans<<"\n";
    }
}