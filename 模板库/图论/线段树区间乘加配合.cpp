#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
ll a[N],tree[N*4],add[N*4],mul[N*4],n,M,q;
void build(int p,int l,int r){
	if(l==r){
		tree[p]=a[l]%M;
		return;
	}
	int m=(l+r)>>1;
	build(p<<1,l,m);
	build(p<<1|1,m+1,r);
	tree[p]=(tree[p<<1]+tree[p<<1|1])%M;
}
void apply(int p,int l,int r,ll mulv,ll addv){
	int len=r-l+1;
	tree[p]=(tree[p]*mulv%M+addv*len%M)%M;
	mul[p]=mul[p]*mulv%M;
	add[p]=(add[p]*mulv%M+addv)%M;
}
void push_down(int p,int l,int r){
	if(mul[p]==1&&add[p]==0) return;
	int m=(l+r)>>1;
	apply(p<<1,l,m,mul[p],add[p]);
	apply(p<<1|1,m+1,r,mul[p],add[p]);
	mul[p]=1;
	add[p]=0;
}
void update(int p,int l,int r,int ql,int qr,ll k,int op){
	if(op==2){
		if(ql<=l&&r<=qr){
			apply(p,l,r,1,k);
			return;
		}
		push_down(p,l,r);
		int m=(l+r)>>1;
		if(ql<=m) update(p<<1,l,m,ql,qr,k,op);
		if(m<qr) update(p<<1|1,m+1,r,ql,qr,k,op);
		tree[p]=(tree[p<<1]+tree[p<<1|1])%M;
	}
	else if(op==1){
		if(ql<=l&&r<=qr){
			apply(p,l,r,k,0);
			return;
		}
		push_down(p,l,r);
		int m=(l+r)>>1;
		if(ql<=m) update(p<<1,l,m,ql,qr,k,op);
		if(m<qr) update(p<<1|1,m+1,r,ql,qr,k,op);
		tree[p]=(tree[p<<1]+tree[p<<1|1])%M;
	}
}
ll query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tree[p];
	push_down(p,l,r);
	int m=(l+r)>>1;
	ll sum=0;
	if(ql<=m) sum=(sum+query(p<<1,l,m,ql,qr))%M;
	if(m<qr) sum=(sum+query(p<<1|1,m+1,r,ql,qr))%M;
	return sum; 
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	for(int i=0;i<N*4;++i) mul[i]=1;
	cin>>n>>q>>M;
	for(int i=1;i<=n;++i) cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=q;++i){
		int op; cin>>op;
		if(op==3){
			int l,r; cin>>l>>r;
			cout<<query(1,1,n,l,r)<<"\n";
		}
		else{
			int l,r; ll k; cin>>l>>r>>k;
			update(1,1,n,l,r,k,op);
		}
	}
}