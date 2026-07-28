#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
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
int prime[]={2,3,5,7,11,61,24251};
mt19937 rnd(time(0));
int randint(int l,int r){
    uniform_int_distribution<int>dis(l,r);
    return dis(rnd);
}
int qpow(int b,int p,int mod){
    int res=1;
    while(p){
        if(p&1)res=res*b%mod;
        b=b*b%mod,p>>=1;
    }
    return res;
}
bool check(int a, int p) {
    int s = p - 1, k;
    for (; ~s & 1; s >>= 1);
    for (k = qpow(a, s, p); s != p - 1 && k != 1 && k != p - 1; k = (int)k * k % p, s <<= 1);
    return k == p - 1 || s & 1;
}
bool isprime(int n) {
    if (n == 1) return 0;
    for (int i = 0; i < 7; i++) {
        if (n == prime[i]) return 1;
        if (n % prime[i] == 0) return 0;
        if (!check(prime[i], n)) return 0;
    }
    for (int i = 1; i <= 10; i++) if (!check(randint(2, n - 1), n)) return 0;
    return 1;
}
int pollard_rho(int n) {
    if (n == 4) return 2;
    if (isprime(n)) return n;
    for (int c, t, r, p, q; ;) {
        c = randint(1, n - 1), t = 0, r = 0, p = 1, q;
        auto f = [=](int x) { return (x * x + c) % n; };
        do {
            for (int i = 0; i < 128; ++i) {
                t = f(t), r = f(f(r));
                if (t == r || (q = (int)p * abs(t - r) % n) == 0) break; p = q;
            }
            int d = __gcd(p, n); if (d > 1) return d;
        } while (t != r);
    }
}

unordered_map<int, int> mp;

int get(int x) {
    if (mp[x]) return mp[x];
    int k = pollard_rho(x);
    return mp[x] = k == x ? x : mp[x] = max(get(k), get(x / k));
}

inline 
void print(int n) {
    if (n < 10) return putchar(n ^ '0'), void();
    print(n / 10), putchar(n % 10 ^ '0');
}

inline 
int solve(int n) {
    int res = (int)n * n;
    for (int k = get(n); ; k = get(n)) {
        for (res -= res / k / k; n % k == 0; n /= k);
        if (n == 1) break;
    }
    mp.clear();
    return res % mod;
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
        while(t--){
            cin>>n;
            int ans=0;
            for(int i=2;i*i<=n;i++)
                if(n%i==0){
                    ans=f[i]*f[n/i]%mod;
                    break;
                }
            if(!ans)ans=n;
            cout<<ans<<"\n";
        }
    }
    if(id==6){
        while(t--){
            
        }
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