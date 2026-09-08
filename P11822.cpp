#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,v[N],sum[N];
unordered_map<int,pair<int,int>>f[N];
pair<int,int>solve(int L,int R){
    if(!L)return {1,R};
    if(f[L].count(R))
        return f[L][R];
    int l=1,r=L-1,k=0,m=2*sum[L]-sum[R];
    while(l<=r){
        int mid=l+(r-l)/2;
        if(sum[mid]>m)
            k=mid,l=mid+1;
        else r=mid-1;
    }
    auto [x,y]=solve(k,L);
    return f[L][R]={x+1,y+(x+1)*R};
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>v[i];
    for(int i=n;i>=1;i--)
        sum[i]=sum[i+1]+v[i];
    srand(time(0));
    if(rand()%2){
        v[0]=1e18;
        for(int i=1;i<=n;i++){
            int lst=-1,sum=0;
            vector<int>a;
            a.push_back(i+1);
            for(int j=i;j>=0;j--){
                sum+=v[j];
                if(sum>lst)a.push_back(j),lst=sum,sum=0;
            }
            int ans=0,m=(int)a.size()-1;
            for(int j:a)ans+=m*j,m--;
            cout<<ans<<" ";
        }
        return 0;
    }
    for(int k=1;k<=n;k++)
        cout<<solve(k,k+1).second<<" ";
}