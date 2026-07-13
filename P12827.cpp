#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int a[N];
int n,q;
struct node{
    int bas[40];
    void init(){
        return memset(bas,0,sizeof bas),void();
    }
    void ins(int x){
        for(int i=30;~i;i--)
            if(bas[i]&&(x&(1<<i)))
                x^=bas[i];
            else if(x&(1<<i)){
                bas[i]=x;
                for(int j=30;j>i;j--)
                    if(bas[j])bas[j]^=x;
                return ;
            }
        return ;
    }
};
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;i++)cin>>a[i],a[i]+=1ll<<30;
        while(q--){
            int op,l,r,x;cin>>op>>l>>r;
            if(op==1){
                init();
                for(int i=l;i<=r;i++)ins(a[i]);
            }
        }
    }
    return 0;
}