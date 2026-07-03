#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
#ifdef ONLINE_JUDGE
    #define getchar getchar_unlocked
#endif
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
}
unsigned int f[N][10],b[N];
int get(int x){
    int w=0,y,pre;
    while(b[w]<=x)w++;
    int ans=0;
    for(int i=1;i<w;i++)
        for(int j=1;j<=9;j++)
            ans+=f[i][j];
    for(int j=1;j<x/b[w-1];j++)ans+=f[w][j];
    pre=x/b[w-1],x%=b[w-1];
    for(int i=w-1;i>=1;i--){
        y=x/b[i-1];
        for(int j=0;j<y;j++)
            if(abs(j-pre)>=2)
                ans+=f[i][j];
        if(abs(pre-y)<2)break;
        pre=y,x%=b[i-1];
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int a,b;cin>>a>>b;
    ::b[0]=1;
    for(int i=1;i<=19;i++)::b[i]=::b[i-1]*10;
    for(int i=0;i<=9;i++)f[1][i]=1;
    for(int i=2;i<=19;i++)
        for(int j=0;j<=9;j++)
            for(int k=0;k<=9;k++)
                if(abs(k-j)>=2)
                    f[i][j]+=f[i-1][k];
    cout<<get(b+1)-get(a);
    return 0;
}