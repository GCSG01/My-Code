#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int n,p,b;
int a[N];
int c[N];
int power(int x,int y){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=p;
        x*=x,x%=p,y>>=1;
    }
    return s;
}
int exgcd(int &x,int &y,int a,int b){
    if(!b)return x=1,y=0,a;
    int g=exgcd(x,y,b,a%b);
    int t=x;
    x=y,y=t-a/b*y;
    return g;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    rd(n),rd(p),rd(b);
    for(int i=1;i<=n;i++)rd(a[i]),a[i]%=p;
    c[1]=1;
    int g=a[1];
    for(int i=2;i<=n;i++){
        int x,y;
        g=exgcd(x,y,g,a[i]);
        for(int j=1;j<i;j++)c[j]*=x,c[j]%=p;
        c[i]=y;
    }
    int x,y;
    g=exgcd(x,y,g,p);
    for(int i=1;i<=n;i++)c[i]=c[i]*x%p;
    if(b%g)return cout<<"NO\n",0;
    cout<<"YES\n";
    // for(int i=1;i<=n;i++)cout<<c[i]<<" ";cout<<"\n";
    for(int i=1;i<=n;i++)
        cout<<(b*c[i]/g%p+p)%p<<" ";
    return 0;
}