#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e6+5;
const double pi=3.141592653;
struct complx{
    double x,y;
    complx(double xx=0,double yy=0){x=xx,y=yy;}
    complx operator+(const complx &B)const{return {x+B.x,y+B.y};}
    complx operator-(const complx &B)const{return {x-B.x,y-B.y};}
    complx operator*(const complx &B)const{return {x*B.x-y*B.y,x*B.y+y*B.x};}
}a[N],b[N];
void fft(int n,complx *a,int c){
    if(n==1)return;
    complx a1[n>>1],a2[n>>1];
    for(int i=0;i<n;i+=2)
        a1[i>>1]=a[i],a2[i>>1]=a[i+1];
    fft(n>>1,a1,c),fft(n>>1,a2,c);
    complx wn=complx(cos(2*pi/n),c*sin(2*pi/n)),w=complx(1,0);
    for(int i=0;i<(n>>1);i++,w=w*wn)
        a[i]=a1[i]+w*a2[i],a[i+(n>>1)]=a1[i]-w*a2[i];
    return ;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=0;i<=n;i++)cin>>a[i].x;
    for(int i=0;i<=m;i++)cin>>b[i].x;
    int lim=1;
    while(lim<=n+m)lim<<=1;
    fft(lim,a,1);
    fft(lim,b,1);
    for(int i=0;i<lim;i++)
        a[i]=a[i]*b[i];
    fft(lim,a,-1);
    for(int i=0;i<=n+m;i++)
        cout<<(int)(a[i].x/lim+0.5)<<" ";
    return 0;
}