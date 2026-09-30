#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3,inf=1e18;
double x[N+5],y[N+5],xx[N+5],yy[N+5];
double t1[N+5],t2[N+5];
inline double dis(int i,int j){
    return sqrt((x[i]-xx[j])*(x[i]-xx[j])+(y[i]-yy[j])*(y[i]-yy[j]));
}
double Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,p,q,r;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>Ax>>Ay,
    cin>>Bx>>By,
    cin>>Cx>>Cy,
    cin>>Dx>>Dy,
    cin>>p>>q>>r;
    double dx=(Bx-Ax)/N,dy=(By-Ay)/N;
    for(int i=0;i<=N;i++)
        x[i]=Ax+dx*i,y[i]=Ay+dy*i,
        t1[i]=sqrt(dx*i*dx*i+dy*i*dy*i)/p;
    dx=(Dx-Cx)/N,dy=(Dy-Cy)/N;
    for(int i=0;i<=N;i++)
        xx[i]=Dx-dx*i,yy[i]=Dy-dy*i,
        t2[i]=sqrt(dx*i*dx*i+dy*i*dy*i)/q;
    double ans=inf;
    for(int i=0;i<=N;i++)
        for(int j=0;j<=N;j++)
            ans=min(ans,t1[i]+t2[j]+dis(i,j)/r);
    printf("%.2lf\n",ans);
}