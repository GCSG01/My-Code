#include<bits/stdc++.h>
using namespace std;
const int N=30;
const double eps=1e-12;
char a[N][N],b[N][N];
int n,m;
int check(char c[][N]){
	int sum=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(c[i][j]==c[n-i+1][m-j+1])sum++;

	return sum;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    random_device rd;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>b[i][j];
    int s=clock();
    while(1){
        if(clock()-s>=1.6*CLOCKS_PER_SEC)break;
        double temp=10000,delta=0.94587;
        while(temp>eps){
            int px,py,op=rd()%2;
            for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++)
                    a[i][j]=b[i][j];
            if(op){
                px=rd()%m+1,py=rd()%m+1;
                for(int i=1;i<=n;i++)
                    swap(a[i][py],a[i][px]);
            }
            else{
                px=rd()%n+1,py=rd()%n+1;
                for(int i=1;i<=m;i++)
                    swap(a[py][i],a[px][i]);
            }
            if(check(a)>check(b)||rd()%10000<=temp){
                if(check(a)>=n*m)return cout<<"YES",0;
                for(int i=1;i<=n;i++)
                    for(int j=1;j<=m;j++)
                        b[i][j]=a[i][j];
            }
            temp*=delta;
        }
    }
    cout<<(check(b)>=n*m?"YES":"NO");
    return 0;
}