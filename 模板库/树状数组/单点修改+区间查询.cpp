#include <bits/stdc++.h>
using namespace std;
const int N=10005;
int tr[N],n;
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
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int m,a;
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a;
		update(i,a);
	}
	for(int i=1;i<=m;++i){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)
			update(x,y);
		else
			cout<<sum(y)-sum(x-1)<<"\n";
	}
}