#include<bits/stdc++.h>
using namespace std;
const int inf=1e6;
string ask(int x,int y){
    cout<<x<<" "<<y<<endl;
    string res;getline(cin,res);
    if(res.find("!")!=string::npos)exit(0);
    return res;
}
string a,b;
int main(){
    ask(0,0),a=ask(1,1),b=ask(0,0);
    if(a==b)
        ask(1,0),ask(0,1);
    int xl=0,xr=inf+1,yl=0,yr=inf+1;
    while(xl<xr||yl<yr){
        int xm=(xl+xr)>>1,ym=(yl+yr)>>1;
        string s1,s2;
        ask(xm,ym);
        if(xm==inf&&ym==inf)s1=s2=b;
		else if(xm==inf)
			s1=b,s2=ask(xm,ym+1);
		else if(ym==inf)
            s1=ask(xm+1,ym),s2=b;
		else s1=ask(xm+1,ym),s2=ask(xm+1,ym+1);
        if(s1==a)xl=xm+1;
        else xr=xm;
        if(s2==a)yl=ym+1;
        else yr=ym;
    }
    ask(xl,yl);
    return 0;
}