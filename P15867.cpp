#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m;
int a[N];

signed main(){
    int t;cin>>t>>t;
    while(t--){
        cin>>n>>m;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int j=m-1;j;j--){
            int flag=1;
            for(int i=1;i<=n;i++)
                if(a[i]&(1<<j)==0){
                    flag=0;
                    break;
                }
            if(flag){
                
            }
        }
    }
    return 0;
}