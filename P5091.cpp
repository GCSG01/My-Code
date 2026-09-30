#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N=5e5+5;
int a,b,m;
inline int rd(){
    long long x;cin>>x;return x;
}
int read(int mod){
    char c;int x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c<='9'&&c>='0'){
        x=x*10+c-'0',c=getchar();
        while(x>mod)x-=mod;
    }
    return x;
}
int qpow(int x,int y,int mod){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return s;
}
void print(int x){
    if(x>9)print(x/10);
    cout<<(long long)(x%10);
}
signed main(){
    // ios::sync_with_stdio(0);cin.tie(0);
    a=rd(),m=rd();
    int mm=m,phi=m;
    for(int i=2;i*i<=m;i++)
        if(mm%i==0){
            phi-=phi/i;
            while(mm%i==0)mm/=i;
        }
    if(mm>1)phi-=phi/mm;
    b=read(phi);
    print(qpow(a,b,m));
}