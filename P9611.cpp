#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int get(int x){
    int ans=0;
    for(int l=1,r;l<=x;l=r+1)
        r=x/(x/l),ans+=(r-l+1)*(x/l);
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int l,r;cin>>l>>r;
    cout<<get(r)-get(l-1);
    return 0;
}