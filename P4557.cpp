#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
struct point{
    double x,y;
}a[N],b[N],s1[N],s2[N],s[N],O;
struct stck{
    int t[N],len;
    void push(int x){t[len++]=x;}
    int operator [](int x){return t[len-x];}
    void pop(){len--;}
    void clear(){t[len=0]=0;}
}st;
point operator +(point a,point b){
    return {a.x+b.x,a.y+b.y};
}
point operator -(point a,point b){
    return {a.x-b.x,a.y-b.y};
}
double operator *(point a,point b){
    return a.x*b.y-b.x*a.y;
}
bool operator ==(point a,point b){
    return a.x==b.x&&a.y==b.y;
}
inline double sqr(double a){
    return a*a;
}
double dis(point a,point b){
    return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
void convex(point *p,int &n){
    int w=1;
    for(int i=1;i<=n;i++)
        if(p[i].y<p[w].y||(p[i].y==p[w].y&&p[i].x<p[w].x))
            w=i;
    swap(p[1],p[w]);
    auto k=p[1];
    sort(p+2,p+n+1,[&](point A,point B){
        return (A-k)*(B-k)==0?dis(A,k)<dis(B,k):(A-k)*(B-k)>0;
    });
    st.clear(),st.push(1),st.push(2);
    for(int i=3;i<=n;i++){
        while(st.len>1&&(p[i]-p[st[2]])*(p[st[1]]-p[st[2]])>=0)st.pop();
        st.push(i);
    }
    n=st.len;
	for(int i=1;i<=n;i++)p[i]=p[st.t[i-1]];
}
void minkowski(int n,int m,int &cnt){
    for(int i=1;i<n;i++)s1[i]=a[i+1]-a[i];
    for(int i=1;i<m;i++)s2[i]=b[i+1]-b[i];
    s1[n]=a[1]-a[n],s2[m]=b[1]-b[m];
    int i=1,j=1;
    s[cnt=1]=a[1]+b[1];
    while(i<=n&&j<=m){
        if(s1[i]*s2[j]>0)s[cnt+1]=s[cnt]+s1[i++];
        else s[cnt+1]=s[cnt]+s2[j++];
        cnt++;
    }
    while(i<=n)s[cnt+1]=s[cnt]+s1[i++],cnt++;
    while(j<=m)s[cnt+1]=s[cnt]+s2[j++],cnt++;
}
bool cmp2(point a,point b){
	double x=a*b;
	if(x==0)return dis(a,O)<dis(b,O);
	else return x>0;
}
bool query(point x,int cnt){
    if(x*s[2]>0||s[cnt]*x>0)return true;
    if(x*s[2]==0&&dis(x,O)>dis(s[2],O))return true;
    if(x*s[cnt]==0&&dis(x,O)>dis(s[cnt],O))return true;
	int w=lower_bound(s+2,s+cnt+1,x,[](point A,point B){
        return A*B==0?dis(A,O)<dis(B,O):A*B>0;
    })-s-1;
	return (x-s[w])*(s[w+1]-s[w])>0;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m,T;cin>>n>>m>>T;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    for(int i=1;i<=m;i++)cin>>b[i].x>>b[i].y,b[i]=O-b[i];
    convex(a,n),convex(b,m);
    int cnt;
    minkowski(n,m,cnt),convex(s,cnt);
    auto k=s[1];
    for(int i=1;i<=cnt;i++)s[i]=s[i]-k;
    while(T--){
        point q;cin>>q.x>>q.y;
        cout<<!query(q-k,cnt)<<"\n";
    }
}