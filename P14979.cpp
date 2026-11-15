#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,k;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--){
		string r;cin>>n>>k>>r;
		int mn=0,mx=0,mind=1e9,flag1=0,flag2=0;
		for(int i=0;i<k;i++){
			int cnt[2]={1,0},pre=0;
			for(int j=i+k;j<n;j+=k)
				pre^=r[j-k]^r[j-k+1],cnt[pre]++;
			if(cnt[0]>=cnt[1])
				mx+=cnt[0],mn+=cnt[1],mind=min(mind,cnt[0]-cnt[1]),flag1^=1;
			else mx+=cnt[1],mn+=cnt[0],mind=min(mind,cnt[1]-cnt[0]),flag2^=1;
		}
		if(flag1!=r[0]-'0')mx-=mind;
		if(flag2!=r[0]-'0')mn+=mind;
		cout<<mn<<" "<<mx<<"\n";
	}
}