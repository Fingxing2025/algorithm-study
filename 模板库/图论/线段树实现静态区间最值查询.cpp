#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod = 998244353;
const int N=100005;
ll a[N],tree[N*4],mark[N*4];
void build(int p,int l,int r){
	if(l==r){
		tree[p]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	tree[p]=max(tree[p*2],tree[p*2+1]);
}
void push_down(int p,int l,int r){
	if(mark[p]!=0){
		int mid=(l+r)>>1;
		mark[p*2]=max(mark[p*2],mark[p]);
		tree[p*2]=max(tree[p*2],mark[p*2]);
		mark[p*2+1]=max(mark[p*2+1],mark[p]);
		tree[p*2+1]=max(tree[p*2+1],mark[p*2+1]);
		mark[p]=0;
	}
}
ll query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)
		return tree[p];
	push_down(p,l,r);
	int mid=(l+r)>>1;
	ll ans=0;
	if(ql<=mid) ans=max(ans,query(p*2,l,mid,ql,qr));
	if(mid<qr) ans=max(ans,query(p*2+1,mid+1,r,ql,qr));
	return ans; 
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	build(1,1,n);
	while(m--){
		int x,y;
		cin>>x>>y;
		cout<<query(1,1,n,x,y)<<"\n";
	}
}
