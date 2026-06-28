#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
const int N=2e5+5;
struct node{
    int a,v,id;
}a[N];
int s[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,c;cin>>n>>c;
        for(int i=1;i<=n;i++)
            cin>>a[i].a,a[i].v=a[i].a+min(i,n-i+1),a[i].id=i;
        sort(a+1,a+n+1,[](node A,node B){
            return A.v<B.v;
        });
        for(int i=1;i<=n;i++)
            s[i]=s[i-1]+a[i].v;
        int ans=0;
        for(int i=1;i<=n;i++){
            int l=0,r=n,cnt=a[i].id+a[i].a;
            if(cnt>c)continue;
            while(l<r){
                int mid=(l+r+1)>>1;
                if(s[mid]+cnt-(i<=mid?a[i].v:0)<=c)l=mid;
                else r=mid-1;
            }
            ans=max(ans,l+(l<i));
        }
        cout<<ans<<"\n";
    }
    return 0;
}