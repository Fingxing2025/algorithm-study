#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;
ll tr1[N],tr2[N],a,lst;
int n,m;
int lowbit(int x){
	return x&-x;
}
void update(int x,ll d,ll tr[]){
	while(x<=n){
		tr[x]+=d;
		x+=lowbit(x);
	}
}
ll sum(int x,ll tr[]){
	ll s=0;
	while(x>0){
		s+=tr[x];
		x-=lowbit(x);
	}
	return s;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a;
		update(i,a-lst,tr1);
		update(i,i*(a-lst),tr2);
		lst=a;
	}
	for(int i=1;i<=m;++i){
		int op,x,y;
		ll d;
		cin>>op;
		if(op==1){
			cin>>x>>y>>d;
			update(x,d,tr1);
			update(y+1,-d,tr1);
			update(x,d*x,tr2);
			update(y+1,-(y+1)*d,tr2);
		}
		else{
			cin>>x>>y;
			cout<<(y+1)*sum(y,tr1)-x*sum(x-1,tr1)-sum(y,tr2)+sum(x-1,tr2)<<"\n";
		}
	}
}
