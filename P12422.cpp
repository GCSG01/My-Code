#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
string s,t;
unordered_map<string,int>f;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        int q;
        f.clear();
        string s;cin>>s>>q;
        while(q--){
            cin>>t;
            if(f.count(t)){
                if(f[t])cout<<"Yes\n";
                else cout<<"No\n";
                continue;
            }
            int k=s.size()/t.size(),sum=k*t.size();
			int i,j,l,r;
			for(i=j=l=r=0;i<s.size()&&l<k;i++){
				if(i-r>s.size()-sum)
                    break;
				if(s[i]==t[j]){
					j++,r++;
					if(j==t.size())
                        j=0,l++;
				}
			}
            if(l>=k)cout<<"Yes\n";
            else cout<<"No\n";
            f[t]=(l>=k);
        }
    }
    return 0;
}