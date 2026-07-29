#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
int pm[]={2,3,5,7,11,23};
int g[N],f[N];
int mu(int n){
    int s=1;
    for(int i=2;i*i<=n;i++)
        if(n%i==0){
            n/=i;
            if(n%i==0)return 0;
            s=-s;
        }
    if(n>1)s=-s;
    return s;
}
void rando(int k){
    f[1]=g[1];
    for(int i=2;i<=k;i++){
        f[i]=g[i];
        for(int j=1;j*j<=i;j++)
            if(i%j==0){
                if(j!=i)f[i]=(f[i]-f[j])%mod;
                if((i/j)!=i&&(i/j)!=j)f[i]=(f[i]-f[i/j])%mod;
            }
    }
}
int phi(int n){
    int s=n;
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
            for(s-=s/i;n%i==0;n/=i);
    if(n>1)s-=s/n;
    return (__int128)s*s%mod;
}
int qpow(int a,int b){
    int s=1;
    while(b){
        if(b&1)s*=a,s%=mod;
        a*=a,a%=mod,b>>=1;
    }
    return s;
}
int is_prim(int x){
    for(int i=2;i*i<=x;i++)
        if(x%i==0)return false;
    return true;
}
int get(int n){
    int sum=114;
    sum=(sum*n+514)%mod;
    sum=(sum*n+1919)%mod;
    sum=(sum*n+810)%mod;
    return sum;
}
int gcd(int a,int b){
    while(b){
        int t=a%b;
        a=b,b=t;
    }
    return a;
}
int mul_mod(int a,int b,int P) {
    return (int)((__int128)a*b%P);
}
int power(int x,int y,int P){
    int s=1;
    while(y){
        if(y&1)s=mul_mod(s,x,P);
        x=mul_mod(x,x,P),y>>=1;
    }
    return s;
}
bool is_prime(int n){
    if(n<2)return 0;
    for(int p:{2,3,5,7,11,13,17,19,23,29,31,37})
        if(n%p==0)return n==p;
    int d=n-1,s=0;
    while(!(d&1))
        d>>=1,s++;
    for(int a:{2,325,9375,28178,
        450775,9780504,1795265022}){
        if (a%n==0)continue;
        int x=power(a%n,d,n);
        if (x==1||x==n-1)continue;
        bool ok=0;
        for (int r=1;r<s;r++){
            x=mul_mod(x,x,n);
            if(x==n-1){
                ok=1;
                break;
            }
        }
        if(!ok)return 0;
    }
    return 1;
}
int pollard_rho(int n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;

    static mt19937_64 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    while (true) {
        int c = uniform_int_distribution<int>(1, n - 1)(rng);
        int y = uniform_int_distribution<int>(0, n - 1)(rng);

        int m = 128;
        int g = 1;
        int r = 1;
        int q = 1;

        int x = 0;
        int ys = y;

        auto f = [&](int v) -> int {
            return (int)(((__int128)v * v + c) % n);
        };

        while (g == 1) {
            x = y;

            for (int i = 0; i < r; ++i) {
                y = f(y);
            }

            int k = 0;

            while (k < r && g == 1) {
                ys = y;
                q = 1;

                int lim = min(m, r - k);

                for (int i = 0; i < lim; ++i) {
                    y = f(y);

                    int diff = (x > y ? x - y : y - x);
                    q = mul_mod(q, diff, n);
                }

                g = gcd(q, n);
                k += lim;
            }

            if (r > (1LL << 62)) {
                g = n;
                break;
            }

            r <<= 1;
        }

        if (g == n) {
            g = 1;

            while (g == 1) {
                ys = f(ys);

                int diff = (x > ys ? x - ys : ys - x);
                g = gcd(diff, n);
            }

            if (g == n) continue;
        }

        if (g > 1 && g < n) return g;
    }
}
void factor(int n,vector<int>& a){
    if(n==1)return ;
    static const int prm[]={
        2,3,5,7,11,13,17,19,23,29,31,37
    };
    for(int i:prm)
        if(n%i==0){
            while(n%i==0)
                a.push_back(i),n/=i;
            factor(n,a);
            return ;
        }
    if(is_prime(n))
        return a.push_back(n),void();
    int cnt=pollard_rho(n);
    factor(cnt,a);
    factor(n/cnt,a);
    return ;
}
int solve(int n){
    if(n==1)return 1;
    vector<int>a;
    factor(n,a);
    sort(a.begin(),a.end());
    int ans=1;
    for(int i=0;i<(int)a.size();){
        int j=i;
        while(j<(int)a.size()&&a[j]==a[i])j++;
        int cnt=j-i,p=a[i]%mod;
        ans=(qpow(p,2*cnt)-qpow(p,2*cnt-2)+mod)%mod*ans%mod;
        i=j;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int k;cin>>k;
    for(int i=1,x;i<=k;i++)cin>>x>>g[x];
    int t,id,n;
    cin>>t>>id;
    if(id==0)while(t--)cin>>n,cout<<(mu(n)+mod)%mod<<"\n";
    if(id==1)while(t--)cin>>n,cout<<"1\n";
    if(id==2)while(t--)cout<<"0\n";
    if(id==3){
        rando(k);
        while(t--)cin>>n,cout<<(f[n]+mod)%mod<<"\n";
    }
    if(id==4){
        while(t--){
            cin>>n;
            __int128 ans=0;
            for(int i=1;i*i<=n;i++)
                if(n%i==0){
                    ans+=phi(i);
                    if(i*i!=n)ans+=phi(n/i);
                    ans%=mod;
                }
            cout<<(int)ans<<"\n";
        }
    }
    if(id==5){
        while(t--)
            cin>>n,cout<<n<<"\n"; 
    }
    if(id==6){
        while(t--)cin>>n,cout<<solve(n)<<"\n";
    }
    if(id==7){
        while(t--){
            cin>>n;
            int ans=1;
            for(int i=2,k;i*i<=n;i++){
                for(k=1;n%i==0;n/=i,k*=i);
                if(k>1)ans=ans*get(k)%mod;
            }
            if(n>1)ans=ans*get(n)%mod;
            cout<<ans<<"\n";
        }
    }
    if(id==8){
        while(t--)
            cin>>n,cout<<n*n%3<<"\n";
    }
    return 0;
}