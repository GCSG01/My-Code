#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5,MX=1874160;
int n,d;
int a[N][5];
int s[5],f[5],t[MX+5],base[5];
inline int get(){
    char c;cin>>c;
    if('0'<=c&&c<='9')return c-'0'+1;
    return c-'a'+11;
}
int calc(int x){
    int sum=0;
    while(x){
        if(x%37!=0)sum++;
        x/=37;
    }
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>d;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=4;j++)
            a[i][j]=get();
    base[1]=1;
    for(int i=2;i<=4;i++)base[i]=base[i-1]*37;
    for(int i=1;i<=n;i++)
        for(int j=0;j<16;j++){
            int cnt=0;
            for(int k=1;k<=4;k++)
                if(j>>(k-1)&1)cnt+=a[i][k]*base[k];
            t[cnt]++;
        }
    for(int i=1;i<=MX;i++)
        s[calc(i)]+=t[i]*(t[i]-1)/2;
    f[4]=s[4];
    f[3]=s[3]-f[4]*4;
    f[2]=s[2]-f[3]*3-f[4]*6;
    f[1]=s[1]-f[2]*2-f[3]*3-f[4]*4;
    f[0]=n*(n-1)/2-f[1]-f[2]-f[3];
    cout<<f[4-d];
}