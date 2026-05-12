#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10005;
int tr[N],n,m,a,lst;
int lowbit(int x){
	return x&-x;
}
void update(int x,int d){
	while(x<=n){
		tr[x]+=d;
		x+=lowbit(x);
	}
}
int sum(int x){
	int s=0;
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
		update(i,a-lst);
		lst=a;
	}
	for(int i=1;i<=m;++i){
		int op,x,y,d;
		cin>>op;
		if(op==1){
			cin>>x>>y>>d;
			update(x,d);
			update(y+1,-d);
		}
		else{
			cin>>x;
			cout<<sum(x)<<"\n";
		}
	}
}
