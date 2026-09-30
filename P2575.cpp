#include<bits/stdc++.h>
using namespace std;
const int N=1005;
bitset<N>p;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,ans=0;cin>>n;
        while(n--){
            int m,x,tot=0,sum=0,cnt;
            cin>>m,p.reset(),cnt=20-m+1;
            while(m--)cin>>x,p[x]=1;
            for(int i=1;i<=20;i++){
                if(!p[i]){
                    cnt--;
                    if(cnt&1)sum^=tot;
                    tot=0;
                }
                else tot++;
            }
            ans^=sum;
        }
        cout<<(ans?"YES":"NO")<<"\n";
    }
}