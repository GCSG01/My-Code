#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=4e4+5;
int n;
struct node{
    int a,b;
}a[N];
int f[N][202];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    int sum=0;
    for(int i=1;i<=n;i++)
        cin>>a[i].a,sum+=a[i].a;
    for(int i=1;i<=n;i++)
        cin>>a[i].b;
    sort(a+1,a+n+1,[](node A,node B){
        return A.b>B.b;
    });
    int tot=0,cnt=0;
    for(int i=1;i<=n;i++){
        cnt+=a[i].b,tot=i;
        if(sum<=cnt)break;
    }
    cout<<tot<<" ";
    memset(f,128,sizeof f);
    f[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=cnt;j>=a[i].b;j--)
            for(int k=1;k<=tot;k++)
                f[j][k]=max(f[j][k],f[j-a[i].b][k-1]+a[i].a);
    int ans=0;
    for(int i=sum;i<=cnt;i++)
        ans=max(ans,f[i][tot]);
    cout<<sum-ans;
    return 0;
}