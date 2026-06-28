#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=1e3+5;
int n,a,b;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>a>>b;
    if(a>1&&b>1)
        return cout<<"NO",0;
    if(a==1&&b==1){
        if(n==2||n==3)return cout<<"NO",0;
        cout<<"YES\n";
        for(int i=1;i<=n;i++,cout<<"\n")
            for(int j=1;j<=n;j++)
                if(i+1==j||j+1==i)cout<<1;
                else cout<<0;
        return 0;
    }
    if(b==1){
        cout<<"YES\n";
        for(int i=1;i<=n;i++,cout<<"\n")
            for(int j=1;j<=n;j++)
                if(i!=j){
                    if(i>=a&&j>=a)cout<<1;
                    else cout<<0;
                }
                else cout<<0;
    }
    else{
        cout<<"YES\n";
        for(int i=1;i<=n;i++,cout<<"\n")
            for(int j=1;j<=n;j++)
                if(i!=j){
                    if(i>=b&&j>=b)cout<<0;
                    else cout<<1;
                }
                else cout<<0;
    }
    return 0;
}