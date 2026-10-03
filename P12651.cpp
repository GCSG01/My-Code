#include<bits/stdc++.h>
using namespace std;
const int N=5e7+5;
int n;
string s,ans;
void solve(){
    cin>>n>>s,s=" "+s,ans=s;
    int a=-1,b=-1,c=n+1;
    for(int i=1;i<=n;i++)
        if(s[i]=='1'){
            a=i;break;
        }
    if(!~a)return cout<<"0\n",void();
    for(int i=a;i<=n;i++)
        if(s[i]=='0'){
            b=i;break;
        }
    if(!~b){
        for(int i=a;i<n;i++)cout<<"1";
        cout<<(a>1)<<"\n";
        return ;
    }
    for(int i=b;i<=n;i++)
        if(s[i]=='1'){
            c=i;break;
        }
    int len=min(b-a,c-b);
    for(int i=n-a+1,j=n,k=n-len;i;i--,j--,k--){
        int A=(j<a)?0:(s[j]-'0'),B=(k<b-len)?0:(s[k]-'0');
        ans[i]=(A^B)+'0';
    }
    for(int i=1;i<=n-a+1;i++)cout<<ans[i];
    cout<<"\n";
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--)solve();
}