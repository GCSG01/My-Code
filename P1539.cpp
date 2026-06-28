#include<bits/stdc++.h>
using namespace std;
const int N=15,mod=10007;
char a[300],b[300];
int f[1<<N][2];
int S[1<<N],tot;
int h[16],t[16];
int n,m;
inline int get(int x,int y){return (x-1)*m+y;}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[get(i,j)];
    if(n<m){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                b[j*n-i+1]=a[get(i,j)];
        for(int i=1;i<=n*m;i++)
            a[i]=b[i];
        swap(n,m);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[get(i,j)]=='1')h[i]+=1<<(m-j);
            if(a[get(i,j)]=='0')t[i]+=1<<(m-j);
        }
    f[1][0]=1;
    for(int i=0;i<(1<<m);i++)
        if(!(i&(i>>1)))S[++tot]=i;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=tot;j++){
            int s=S[j];
            if((h[i]&s)!=h[i])continue;
            if((t[i]&(~s))!=t[i])continue;
            for(int k=1;k<=tot;k++)
                if(!(s&S[k]))
                    f[j][i%2]+=f[k][(i-1)%2],f[j][i%2]%=mod;
        }
        for(int j=1;j<=tot;j++)
            f[j][(i-1)%2]=0;
    }
    int ans=0;
    for(int i=1;i<=tot;i++)
        ans+=f[i][n%2],ans%=mod;
    cout<<ans;
    return 0;
}