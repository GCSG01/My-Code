#include<bits/stdc++.h>
#include<ext/rope>
const int N=1<<22+7;
using namespace std;
int n,k,cnt;
char now,inst[N],goal[N],bac[N];
struct readers{
	char now;
	bool state;
	readers operator >>(int &goal){
		goal = 0;
		state = true;
		while (now = getchar(), now < 48 || now > 57)state = now^45;
		while (48 <= now && now <= 57){
			goal = (goal<<1) + (goal<<3) + (now^48);
			now = getchar();
		}
		if (!state)goal = -goal;
		return *this;
	}
}in;
__gnu_cxx::rope<char>a,b,tmp;
int main(){
	in>>n;
	while(n--){
		scanf("%s",inst);
		if (inst[0]=='I'||inst[0]=='M'||inst[0]=='D'||inst[0]=='R'){
            in>>k;
			if(inst[0]=='M')cnt=k;
			else if(inst[0]=='I'){
				register int length=a.size();
				for (int i=0;i<k;i++)
					bac[k-i-1]=goal[i]=getchar();
				goal[k]=bac[k]='\0';
				a.insert(cnt,goal);
				b.insert(length-cnt,bac);
			}
            else if(inst[0]=='D'){
				register int length=a.size();
				a.erase(cnt,k);
				b.erase(length-cnt-k,k);
			}
            else if(inst[0]=='R'){
				int length=a.size();
				tmp=a.substr(cnt,k);
				a=a.substr(0,cnt)+b.substr(length-cnt-k,k)+a.substr(cnt+k,length-cnt-k);
				b=b.substr(0,length-cnt-k)+tmp+b.substr(length - cnt, cnt);
			}
		}
        else if(inst[0]=='P')cnt--;
		else if(inst[0]=='N')cnt++;
		else if(inst[0]=='G'){
			putchar(a[cnt]);
			if(a[cnt]!=10)putchar(10);
		}
	}
    // cout<<endl;
	return 0;
}