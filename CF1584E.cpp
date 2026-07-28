#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
map<int,int>t;
int n;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n,t.clear();
        int f=1,s=0,ans=0;
        for(int i=1;i<=n;i++){
            int x;cin>>x;
            t[f*s]++,f=-f,s=x-s;
            while(!t.empty())
                if(f>0){
                    auto it=*--t.end();
                    if(it.first>s)t.erase(--t.end());
                    else break;
                }
                else{
                    auto it=*t.begin();
                    if(it.first<f*s)t.erase(t.begin());
                    else break;
                }
            ans+=t[f*s];
        }
        cout<<ans<<"\n";
    }
    return 0;
}