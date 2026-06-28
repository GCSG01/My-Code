#include<bits/stdc++.h>
#define int long long
using namespace std;
void rd(int &x){
    char c=getchar();x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
void exgcd(int a,int b,int &x,int &y){
    if(!b)return x=1,y=0,void();
    exgcd(b,a%b,y,x),y-=a/b*x;
    return ;
}
int inv(int x,int p){
    exgcd(x,p,x,*new int);
    return (x%p+p)%p;
}
int bsgs(int a,int p,int b){
    a%=p,b%=p;
    int A=1,B=sqrt(p)+1;
    map<int,int>f;
    for(int i=1;i<=B;i++)
        A=A*a%p,f[A*b%p]=i;
    for(int i=1,cnt=A;i<=B;i++){
        if(f.count(cnt))
            return i*B-f[cnt];
        cnt=cnt*A%p;
    }
    return -1;
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int exbsgs(int a,int p,int b){
    int d=__gcd(a,p),k=0;
    a%=p,b%=p;
    // cout<<d<<"\n";
    while(d>1){
        if(b==1)return k;
        if(b%d)return -1;
        p/=d;
        b=b/d*inv(a/d,p)%p;
        d=__gcd(p,a%=p);
        k++;
    }
    int ans=bsgs(a,p,b);
    return ans==-1?-1:ans+k;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int a,p,b,Ans=0;
    while((cin>>a>>p>>b)&&a){
        Ans=exbsgs(a,p,b);
        if(Ans==-1)cout<<"No Solution\n";
        else cout<<Ans<<"\n";
    }
    return 0;
}