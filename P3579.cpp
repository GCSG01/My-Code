#include<bits/stdc++.h>
// #define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;rd(T);
    while(T--){
        int a,b,c,d;rd(a),rd(b),rd(c),rd(d);
        a--,c--;
        int ans=0;
        for(int l=1,r;l<=min(b,d);l=r+1){
            r=min(b/(b/l),d/(d/l));
            if(a/r<b/r&&c/r<d/r)
                ans=r;
        }
        cout<<ans<<"\n";
    }
    return 0;
}