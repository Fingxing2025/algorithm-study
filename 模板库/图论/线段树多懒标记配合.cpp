#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
bool is_set[N*4];
ll tree[N*4],m_set[N*4],m_add[N*4],a[N];
int n,q;
void build(int p,int l,int r){
	if(l==r){
		tree[p]=a[l];
		return;
	}
	int m=(l+r)>>1;
	build(p<<1,l,m);
	build(p<<1|1,m+1,r);
	tree[p]=max(tree[p<<1],tree[p<<1|1]);
}
void push_down(int p){
	if(is_set[p]){
		tree[p<<1]=tree[p<<1|1]=m_set[p];
		m_set[p<<1]=m_set[p<<1|1]=m_set[p];
		is_set[p<<1]=is_set[p<<1|1]=true;
		m_add[p<<1]=m_add[p<<1|1]=0;
		is_set[p]=false;
		m_set[p]=0;
	}
	if(m_add[p]!=0){
		tree[p<<1]+=m_add[p];
		tree[p<<1|1]+=m_add[p];
		m_add[p<<1]+=m_add[p];
		m_add[p<<1|1]+=m_add[p];
		m_add[p]=0;
	}
}
void update(int p,int l,int r,int ql,int qr,ll v,int op){
	if(op==1){
		if(ql<=l&&r<=qr){
			m_add[p]=0;
			m_set[p]=v;
			is_set[p]=true;
			tree[p]=v;
			return;
		}
		push_down(p);
		int m=(l+r)>>1;
		if(ql<=m) update(p<<1,l,m,ql,qr,v,op);
		if(m<qr) update(p<<1|1,m+1,r,ql,qr,v,op);
		tree[p]=max(tree[p<<1],tree[p<<1|1]);
	}
	else if(op==2){
		if(ql<=l&&r<=qr){
			m_add[p]+=v;
			tree[p]+=v;
			return;
		}
		push_down(p);
		int m=(l+r)>>1;
		if(ql<=m) update(p<<1,l,m,ql,qr,v,op);
		if(m<qr) update(p<<1|1,m+1,r,ql,qr,v,op);
		tree[p]=max(tree[p<<1],tree[p<<1|1]);
	}
}
ll query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tree[p];
	push_down(p);
	ll ans=LLONG_MIN;
	int m=(l+r)>>1;
	if(ql<=m) ans=max(query(p<<1,l,m,ql,qr),ans);
	if(m<qr) ans=max(query(p<<1|1,m+1,r,ql,qr),ans);
	return ans;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=q;++i){
		int op; cin>>op;
		if(op==3){
			int l,r; cin>>l>>r;
			cout<<query(1,1,n,l,r)<<"\n";
		}
		else{
			int l,r; ll x; cin>>l>>r>>x;
			update(1,1,n,l,r,x,op);
		}
	}
}