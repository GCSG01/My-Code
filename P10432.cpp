#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=305;
int n,K;
int h[N],c[N],a[N],cnt[N],mn[N];
__int128 f[N][N][N];
unordered_set<int>st;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    memset(mn,0x3f,sizeof mn);
    memset(f,0x3f,sizeof f);
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>h[i]>>c[i],a[i]=h[i];
        while(st.find(a[i])!=st.end())a[i]++;
        st.insert(a[i]);
    }
	sort(a+1,a+n+1),a[n+1]=a[n]+1;
    int nn=n+1;
	for(int i=1;i<=n;i++)
        h[i]=lower_bound(a+1,a+nn+1,h[i])-a,mn[h[i]]=min(mn[h[i]],c[i]),cnt[h[i]]++;
    f[1][1][cnt[1]-1]=0;
    for(int i=1;i<nn;i++)
        for(int j=1;j<=n;j++)
            for(int k=0;k<=n;k++){
                f[i][j+1][k]=min(f[i][j+1][k],f[i][j][k]+mn[i]);
                int l=max(0ll,cnt[i+1]+k-j);
                f[i+1][j][l]=min(f[i+1][j][l],f[i][j][k]+K*k*(a[i+1]-a[i]));
            }
    int ans=1e18;
    for(int i=0;i<=n;i++)
        if(f[nn][i][0]<=ans)
            ans=f[nn][i][0];
    cout<<ans;
    return 0;
}