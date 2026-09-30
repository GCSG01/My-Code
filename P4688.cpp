#include<bits/stdc++.h>
#include<immintrin.h>
#pragma GCC target("avx2,popcnt")
using namespace std;
const int N=1e5+5,B=10000,Q=B*3+5;
const int W=(N+63)>>6,P=(W+3)&~3;
const int RB=12,RV=1<<RB,RM=RV-1;
using ull=unsigned long long;
alignas(32) ull k[B+5][P],F[P];
int n,m,a[N],b[N],t[N],Ans[B+5];
unsigned char vis[B+5];
struct node{
    int l,r,id,key;
}qu[Q],tmp[Q];
int rc[RV];
namespace IO{
    const int SZ=1<<20;
    char ibuf[SZ],obuf[SZ];
    int ip,il,op;
    inline char gc(){
        if(ip==il)
            il=fread(ibuf,1,SZ,stdin),ip=0;
        return il?ibuf[ip++]:0;
    }
    inline int read(){
        int x=0;
        char c=gc();
        while(c<'0'||c>'9')c=gc();
        while(c>='0'&&c<='9')
            x=x*10+c-'0',c=gc();
        return x;
    }
    inline void pc(char c){
        if(op==SZ)
            fwrite(obuf,1,op,stdout),op=0;
        obuf[op++]=c;
    }
    inline void write(int x){
        char s[12];
        int t=0;
        if(!x)return pc('0');
        while(x)
            s[t++]=x%10+'0',x/=10;
        while(t)
            pc(s[--t]);
        pc('\n');
    }
    inline void flush(){
        if(op)
            fwrite(obuf,1,op,stdout),op=0;
    }
}
inline void add(int x){
    int p=x+t[x]++;
    F[p>>6]|=1ull<<(p&63);
}
inline void del(int x){
    int p=x+(--t[x]);
    F[p>>6]&=~(1ull<<(p&63));
}
inline void And(int id){
    ull* __restrict p=k[id];
    const ull* __restrict f=F;
    int i=0;
    for(;i+15<P;i+=16){
        __m256i x0=_mm256_load_si256((const __m256i*)(p+i));
        __m256i y0=_mm256_load_si256((const __m256i*)(f+i));
        _mm256_store_si256((__m256i*)(p+i),_mm256_and_si256(x0,y0));
        __m256i x1=_mm256_load_si256((const __m256i*)(p+i+4));
        __m256i y1=_mm256_load_si256((const __m256i*)(f+i+4));
        _mm256_store_si256((__m256i*)(p+i+4),_mm256_and_si256(x1,y1));
        __m256i x2=_mm256_load_si256((const __m256i*)(p+i+8));
        __m256i y2=_mm256_load_si256((const __m256i*)(f+i+8));
        _mm256_store_si256((__m256i*)(p+i+8),_mm256_and_si256(x2,y2));
        __m256i x3=_mm256_load_si256((const __m256i*)(p+i+12));
        __m256i y3=_mm256_load_si256((const __m256i*)(f+i+12));
        _mm256_store_si256((__m256i*)(p+i+12),_mm256_and_si256(x3,y3));
    }
    for(;i<P;i++)
        p[i]&=f[i];
}
inline int count(int id){
    const ull* p=k[id];
    int s0=0,s1=0,s2=0,s3=0,i=0;
    for(;i+7<P;i+=8){
        s0+=__builtin_popcountll(p[i]);
        s1+=__builtin_popcountll(p[i+1]);
        s2+=__builtin_popcountll(p[i+2]);
        s3+=__builtin_popcountll(p[i+3]);
        s0+=__builtin_popcountll(p[i+4]);
        s1+=__builtin_popcountll(p[i+5]);
        s2+=__builtin_popcountll(p[i+6]);
        s3+=__builtin_popcountll(p[i+7]);
    }
    for(;i<P;i++)
        s0+=__builtin_popcountll(p[i]);
    return s0+s1+s2+s3;
}
inline void radix_sort(int q){
    node *s=qu,*d=tmp;
    for(int sh=0;sh<36;sh+=RB){
        memset(rc,0,sizeof rc);
        for(int i=1;i<=q;i++)
            ++rc[(s[i].key>>sh)&RM];
        for(int i=1;i<RV;i++)
            rc[i]+=rc[i-1];
        for(int i=q;i;i--)
            d[rc[(s[i].key>>sh)&RM]--]=s[i];
        swap(s,d);
    }
    if(s!=qu)memcpy(qu+1,s+1,q*sizeof(node));
}
void solve(int q){
    int cnt=q/3;
    int bk=5*n/(4*sqrt(q));
    if(bk<1)bk=1;
    if(bk>n)bk=n;
    memset(t,0,sizeof t);
    memset(vis,0,cnt+1);
    memset(F,0,sizeof F);
    for(int i=1;i<=q;i++){
        int bl=(qu[i].l-1)/bk;
        qu[i].key=(bl<<17)|(bl&1?qu[i].r:n-qu[i].r);
    }
    radix_sort(q);
    int l=1,r=0;
    for(int i=1;i<=q;i++){
        while(l>qu[i].l)add(a[--l]);
        while(r<qu[i].r)add(a[++r]);
        while(l<qu[i].l)del(a[l++]);
        while(r>qu[i].r)del(a[r--]);
        int id=qu[i].id;
        if(!vis[id])
            memcpy(k[id],F,sizeof F),vis[id]=1;
        else And(id);
    }
    for(int i=1;i<=cnt;i++)
        IO::write(Ans[i]-3*count(i));
}
int main(){
    n=IO::read(),m=IO::read();
    for(int i=1;i<=n;i++)
        a[i]=IO::read(),b[i]=a[i];
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    int q=0,tot=0;
    for(int i=1;i<=m;i++){
        int id=i-tot;Ans[id]=0;
        for(int j=1;j<=3;j++)
            ++q,qu[q].l=IO::read(),qu[q].r=IO::read(),qu[q].id=id,Ans[id]+=qu[q].r-qu[q].l+1;
        if(i%B==0)
            solve(q),tot=i,q=0;
    }
    if(q)solve(q);
    IO::flush();
    return 0;
}