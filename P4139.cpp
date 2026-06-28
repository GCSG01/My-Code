#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
int f[N];
vector<int>p;
int phi[N];
void init(){
    phi[1]=1;
    for(int i=2;i<=N-5;i++){
        if(!f[i])p.push_back(i),phi[i]=i-1;
        for(int j:p){
            if(i*j>N-5)break;
            f[i*j]=1;
            if(i%j==0){
                phi[i*j]=phi[i]*j;
                break;
            }
            else phi[i*j]=phi[i]*phi[j];
        }
    }
    return ;
}
int power(int x,int y,int p){
    int s=1;
    while(y){
        if(y&1)s*=x,s%=p;
        x*=x,x%=p,y>>=1;
    }
    return s;
}
int get(int p){
    // cout<<p<<" "<<phi[p]<<"\n";
    if(p<=1)return 0;
    return power(2,get(phi[p])+phi[p],p);
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    init();
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        cout<<get(n)<<"\n";
    }
    return 0;
}