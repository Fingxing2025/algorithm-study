#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
ll A,B,C,t[N],b[N];
int n,m;
ll f(ll p){
	ll ans=0,x=0,y=0;
	for(int i=1;i<=m;++i){
		if(b[i]<p) x+=p-b[i];
		else y+=b[i]-p;
	}
	if(A<B){
		if(x<y){
			ans+=x*A;
			y-=x;
		}
		else{
			ans+=y*A;
			y=0;
		}
	}
	ans+=y*B;
	for(int i=1;i<=n;++i)
		if(t[i]<p) ans+=(p-t[i])*C;
	return ans;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>A>>B>>C>>n>>m;
	for(int i=1;i<=n;++i) cin>>t[i];
	for(int i=1;i<=m;++i) cin>>b[i];
	sort(t+1,t+n+1); sort(b+1,b+m+1);
	if(C==1e16){
		cout<<f(t[1]);
		return 0;
	} 
	if(A==1e9&&B==1e9){
		cout<<f(b[m]);
		return 0;
	}
	ll l=t[1],r=b[m];
	while(r-l>2){
		int k=(r-l)/3;
		int m1=l+k,m2=r-k;
		if(f(m1)>f(m2)) l=m1;
		else r=m2;
	}
	ll ans=1e18;
	for(int i=l;i<=r;++i)
		ans=min(ans,f(i));
	cout<<ans;
}
