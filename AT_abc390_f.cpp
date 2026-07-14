#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,a[N],ans;
vector<int>pos[N];

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
	for(int i=0;i<=n;i++)
        pos[i].push_back(0);
	for(int i=1;i<=n;i++)
        cin>>a[i],pos[a[i]].push_back(i);
    for(int i=0;i<=n;i++)
        pos[i].push_back(n+1);
	for(int i=1;i<=n;i++){
        const auto& v1=pos[a[i]-1];
        auto it1=lower_bound(v1.begin(),v1.end(),i);
        int s1=it1-v1.begin();
        int l1=v1[s1-1],r1=v1[s1];

        const auto& v2=pos[a[i]];
        auto it2=lower_bound(v2.begin(),v2.end(),i);
        int s2=it2-v2.begin();
        int l2=v2[s2-1];

        ans+=(r1-i)*(i-max(l1,l2));
	}
    cout<<ans;
    return 0;
}