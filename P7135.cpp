#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int mp[3][3],vis[3][N],z[3][3]={{2,9,4},{7,5,3},{6,1,8}},x[10],y[10];
double ans[3][N];
int over(){
	for(int i=0;i<3;i++){
		if(mp[i][0]==mp[i][1]&&mp[i][1]==mp[i][2]&&mp[i][0])
            return mp[i][0];
		if(mp[0][i]==mp[1][i]&&mp[1][i]==mp[2][i]&&mp[0][i])
            return mp[0][i];
	}
	if(mp[0][0]==mp[1][1]&&mp[1][1]==mp[2][2]&&mp[0][0])
        return mp[0][0];
	if(mp[0][2]==mp[1][1]&&mp[1][1]==mp[2][0]&&mp[0][0])
        return mp[0][2];
	return 0;
}
bool full(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
            if(!mp[i][j])return 0;
	return 1;
}
int zip(){
	int sum=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
            sum=sum*3+(mp[i][j]+1);
	return sum;
}
double dfs(int now){
	int x=over(),u=zip();
	double sum=min(0,-now),re2=-now;
	int cnt=0;
	if(x)return x;
	if(vis[now+1][u])return ans[now+1][u];
	if(full())return 0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(mp[i][j]==0){
				mp[i][j]=now;
				cnt++;
				if(now==-1)
                    sum+=dfs(-now),re2=min(dfs(-now),re2);
				else sum=max(sum,dfs(-now)),re2=max(dfs(-now),re2);
				mp[i][j]=0;
			}
	vis[now+1][u]=1;
	if(now==-1)sum/=cnt;
	return ans[now+1][u]=(sum+re2)/2;
} 
extern "C" int choose(int v){
	if(v)mp[x[v]][y[v]]=-1;
	int x=0,y=0;
	double mx=-1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(mp[i][j]==0){
				mp[i][j]=1;
				if(dfs(-1)>mx)
					mx=dfs(-1),x=i,y=j;
				mp[i][j]=0;
			}
	mp[x][y]=1;
	return z[x][y];
}
extern "C" void init(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
            x[z[i][j]]=i,y[z[i][j]]=j;
    return ;
}
extern "C" void newgame(int flag) {
	memset(mp,0,sizeof(mp));
}