#include<bits/stdc++.h>
const double PI=acos(-1);
using namespace std;
namespace geometry{
    struct Point{
        double x,y;
        Point(double x=0,double y=0):x(x),y(y){}
    };
    typedef Point Vector;
    Vector operator+(Vector a,Vector b){
        return Vector(a.x+b.x,a.y+b.y);
    }
    Vector operator-(Vector a,Vector b){
        return Vector(a.x-b.x,a.y-b.y);
    }
    Vector operator*(Vector a,double p){
        return Vector(a.x*p,a.y*p);
    }
    Vector operator/(Vector a,double p){
        return Vector(a.x/p,a.y/p);
    }
    bool operator<(const Point &a,const Point &b){
        return a.x<b.x||(a.x==b.x&&a.y<b.y);
    }
    const double eps=1e-10;
    int dcmp(double x){
        if(fabs(x)<eps)return 0;
        else return x<0?-1:1;
    }
    bool operator==(const Point &a,const Point &b){
        return (!dcmp(a.x-b.x))&&(!dcmp(a.y-b.y));
    }
    double dot(Vector a,Vector b){
        return a.x*b.x+a.y*b.y;
    }
    double length(Vector a){
        return sqrt(dot(a,a));
    }
    double angle(Vector a,Vector b){
        return acos(dot(a,b)/length(a)/length(b));
    }
    double cross(Vector a,Vector b){
        return a.x*b.y-a.y*b.x;
    }
    double area_2(Point a,Point b,Point c){
        return cross(b-a,c-a);
    }
    double length(Point a,Point b){
        return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    }
    Vector rotate(Vector a,double rad){
        return Vector(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
    }
    Vector normal(Vector a){
        double l=length(a);
        return Vector(-a.y/l,a.x/l);
    }
    int ConvexHull(int siz,Point p[],Point ans[]){
        sort(p+0,p+siz);int tp=0;
        for(int i=0;i<siz;i++){
            while(tp>1&&cross(ans[tp-1]-ans[tp-2],p[i]-ans[tp-2])<=0)tp--;
            ans[tp++]=p[i];
        }
        int k=tp;
        for(int i=siz-2;i>=0;i--){
            while(tp>k&&cross(ans[tp-1]-ans[tp-2],p[i]-ans[tp-2])<=0)tp--;
            ans[tp++]=p[i];
        }
        if(siz>1)tp--;
        return tp;
    }
}
using namespace geometry;
const int N=5e5+5;
int n;
double a,b,d;
Point p[N],p2[N];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>a>>b>>d,d*=2,a-=d,b-=d;
    for(int i=0;i<n;i++){
        double x,y,k;cin>>x>>y>>k;
        p[i<<2|0]=rotate(Vector(b/2,a/2),k)+Vector(x,y);
        p[i<<2|1]=rotate(Vector(-b/2,a/2),k)+Vector(x,y);
        p[i<<2|2]=rotate(Vector(-b/2,-a/2),k)+Vector(x,y);
        p[i<<2|3]=rotate(Vector(b/2,-a/2),k)+Vector(x,y);
    }
    int sz=ConvexHull(n<<2,p,p2);
    double sum=d*PI+length(p2[sz-1],p2[0]);
    for(int i=1;i<sz;i++)
        sum+=length(p2[i],p2[i-1]);
    cout<<fixed<<setprecision(2)<<sum;
    return 0;
}