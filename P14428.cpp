#include<bits/stdc++.h>
#define int long long//计算几何爆int?
using namespace std;
const int N=2e5+5;
struct node{
    int x,y,c;
    int operator*(node B)const{
        return x*B.y-y*B.x;
    }
}a[N],b[N];
int n,ans;
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y>>a[i].c;
    for(int i=1;i<=n;i++){
        for(int j=1,tot=0;j<=n;j++)
            if(i!=j)b[++tot]={a[j].x-a[i].x,a[j].y-a[i].y,a[j].c};//以当前点为原点重新建系
        sort(b+1,b+n,[](node A,node B){
            if(!A.x&&!A.y)return true;
            if(!B.x&&!B.y)return false;
            return atan2(A.y,A.x)>atan2(B.y,B.x);//极角排序
        });
        int s[2][4]={0,0,0,0,0,0,0,0},pos=1;//sum,指针
        s[1][b[1].c]++,s[0][a[i].c]++;
        for(int j=2;j<n;j++)s[0][b[j].c]++;
        while(pos<n-1&&b[1]*b[pos+1]<=0)
            pos++,s[0][b[pos].c]--,s[1][b[pos].c]++;

        ans+=s[0][0]*s[0][1]*s[0][2]/s[0][a[i].c]*s[1][0]*s[1][1]*s[1][2]/s[1][b[1].c];
        //统计在第一个顶点的答案

        for(int j=2;j<n;j++){
            s[1][b[j-1].c]--,s[0][b[j-1].c]++;
            while(1){
                if(pos==n-1)pos=0;
                if(b[j]*b[pos+1]>0||(pos+1==j&&s[1][b[j].c]>0))break;
                pos++,s[0][b[pos].c]--,s[1][b[pos].c]++;//移动指针
            }
            ans+=s[0][0]*s[0][1]*s[0][2]/s[0][a[i].c]*s[1][0]*s[1][1]*s[1][2]/s[1][b[j].c];
        }
    }
    cout<<ans/2;//一对三角形会被两条直线统计
    return 0;
}