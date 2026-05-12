#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
ll s[N],d[N];
int a,b,c,m,ans;
struct attack{
	int x1,y1,z1,x2,y2,z2;
	ll num;
}t[N];
int id(int x,int y,int z){
	if(x>a||y>b||z>c) return 0;
	return (x-1)*b*c+(y-1)*c+(z-1)+1;
}
bool check(int p){
	memset(d,0,sizeof(d));
	for(int i=1;i<=p;++i){
		int x1=t[i].x1,y1=t[i].y1,z1=t[i].z1,x2=t[i].x2,y2=t[i].y2,z2=t[i].z2; 
		ll num=t[i].num;
		d[id(x1,y1,z1)]+=num;
		d[id(x2+1,y1,z1)]-=num;
		d[id(x1,y2+1,z1)]-=num;
		d[id(x1,y1,z2+1)]-=num;
		d[id(x1,y2+1,z2+1)]+=num;
		d[id(x2+1,y1,z2+1)]+=num;
		d[id(x2+1,y2+1,z1)]+=num;
		d[id(x2+1,y2+1,z2+1)]-=num;
	}
	for(int i=1;i<=a;++i)
		for(int j=1;j<=b;++j)
			for(int k=1;k<c;++k)
				d[id(i,j,k+1)]+=d[id(i,j,k)];
	for(int i=1;i<=a;++i)
		for(int j=1;j<b;++j)
			for(int k=1;k<=c;++k)
				d[id(i,j+1,k)]+=d[id(i,j,k)];
	for(int i=1;i<a;++i)
		for(int j=1;j<=b;++j)
			for(int k=1;k<=c;++k)
				d[id(i+1,j,k)]+=d[id(i,j,k)];
	for(int i=1;i<=a;++i)
		for(int j=1;j<=b;++j)
			for(int k=1;k<=c;++k)
				if(d[id(i,j,k)]>s[id(i,j,k)])
					return true;
	return false;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>a>>b>>c>>m;
	for(int i=1;i<=a;++i)
		for(int j=1;j<=b;++j)
			for(int k=1;k<=c;++k)
				cin>>s[id(i,j,k)];
	for(int i=1;i<=m;++i)
		cin>>t[i].x1>>t[i].x2>>t[i].y1>>t[i].y2>>t[i].z1>>t[i].z2>>t[i].num;
	int l=1,r=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	cout<<ans<<"\n";
}
