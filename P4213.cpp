#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=8e6+5;
int phi[N],mu[N];
int sphi[N],smu[N];
int p[N],tot,vis[N];
unordered_map<int,int>Ans1,Ans2;
int m;
void init(){
    phi[1]=mu[1]=1;
    for(int i=2;i<=m;i++){
        if(!vis[i])
            p[++tot]=i,phi[i]=i-1,mu[i]=-1;
        for(int j=1;j<=tot&&i*p[j]<=m;j++){
            vis[i*p[j]]=1;
            if(i%p[j]){
                phi[i*p[j]]=phi[i]*(p[j]-1);
                mu[i*p[j]]=-mu[i];
            }
            else{
                phi[i*p[j]]=phi[i]*p[j];
                mu[i*p[j]]=0;
                break;
            }
        }
    }
    for(int i=1;i<=m;i++)
        sphi[i]=sphi[i-1]+phi[i],
        smu[i]=smu[i-1]+mu[i];
    return ;
}
int ans1(int x){
    if(x<=m)return sphi[x];
    if(Ans1.count(x))return Ans1[x];
    int ans=x*x+x;ans>>=1;
    for(int l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        ans-=(r-l+1)*ans1(x/l);
    }
    return Ans1[x]=ans;
}
int ans2(int x){
    if(x<=m)return smu[x];
    if(Ans2.count(x))return Ans2[x];
    int ans=1;
    for(int l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        ans-=(r-l+1)*ans2(x/l);
    }
    return Ans2[x]=ans;
}
int qu[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    int mx=0;
    for(int i=1;i<=T;i++)cin>>qu[i],mx=max(mx,qu[i]);
    m=pow(T*mx,2.0/3); 
    init();
    for(int i=1;i<=T;i++)
        cout<<ans1(qu[i])<<" "<<ans2(qu[i])<<"\n";
    return 0;
}