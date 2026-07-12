#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+5;
string S;
int a[N];
int s[N];
int c[N];
int g[N];
int F[N];
int n;
int get(int x){
    return (x>0)?(int)log10(x)+1:1;
}
int suf[10];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>S;S=S+"+";
    int cnt=0,f=1;
    for(int i=0;i<S.size();i++){
        if(S[i]=='+')
            a[++n]=cnt*f,F[n]=f,cnt=0,f=1;
        else if(S[i]=='-')
            a[++n]=cnt*f,F[n]=f,cnt=0,f=-1;
        else cnt=cnt*10+S[i]-'0';
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        s[i]=max(s[i-1]+a[i],abs(a[i]));
    for(int i=1;i<=n;i++)ans=max(ans,s[i]);
    cout<<ans<<"\n";
    for(int i=n;i>=0;i--)
        c[i]=max(g[i+1]+abs(a[i]),abs(a[i])),
        g[i]=max(g[i+1]+a[i],a[i]);
    for(int i=n;i>=1;i--)
        g[i]=c[i],c[i]=max(c[i],c[i+1]);
    for(int i=0;i<=n;i++)
        ans=max(ans,s[i]+c[i+1]);
    cout<<ans<<"\n";
    for(int j=0;j<=9;j++)suf[j]=-1;
    for(int i=n;i>=1;i--){
        int cnt=0;
        if(a[i]>=0)cnt=s[i-1];
        for(int j=0;j<=9;j++)
            if(suf[j]!=-1)
                ans=max(ans,
                cnt+abs(a[i])*(long long)pow(10,j)+suf[j]);
        int w=get(abs(a[i]));
        suf[w]=max(g[i],suf[w]);
    }
    cout<<ans;
    return 0;
}