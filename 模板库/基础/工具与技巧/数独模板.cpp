#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int row[9],col[9],blk[3][3],m[9][9],ans=-1;
int score[9][9]={
{6,6,6,6,6,6,6,6,6},
{6,7,7,7,7,7,7,7,6},
{6,7,8,8,8,8,8,7,6},
{6,7,8,9,9,9,8,7,6},
{6,7,8,9,10,9,8,7,6},
{6,7,8,9,9,9,8,7,6},
{6,7,8,8,8,8,8,7,6},
{6,7,7,7,7,7,7,7,6},
{6,6,6,6,6,6,6,6,6}};
void flip(int r,int c,int val){
	int bit=1<<(val-1);
	row[r]^=bit;
	col[c]^=bit;
	blk[r/3][c/3]^=bit;
}
void update(){
	int sum=0;
	for(int i=0;i<9;++i)
		for(int j=0;j<9;++j)
			sum+=score[i][j]*m[i][j];
	ans=max(ans,sum);
}
void dfs(int cnt){
	if(cnt==0){
		update();
		return;
	}
	int r,c,op=10,p;
	for(int i=0;i<9;++i)
		for(int j=0;j<9;++j)
			if(m[i][j]==0){
				int ps=~(row[i]|col[j]|blk[i/3][j/3])&0x1ff;
				int ops=0,x=ps;
				while(x>0){
					ops+=x&1;
					x>>=1;
				}
				if(ops==0) return;
				if(ops<op){
					op=ops; p=ps;
					r=i; c=j;
				}
			}
	while(p>0){
		int val=1,x=p;
		while(!(x&1)){
			++val;
			x>>=1;
		}
		m[r][c]=val;
		flip(r,c,val);
		dfs(cnt-1);
		flip(r,c,val);
		m[r][c]=0;
		p&=p-1;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt=0;
	for(int i=0;i<9;++i)
		for(int j=0;j<9;++j){
			cin>>m[i][j];
			if(m[i][j]!=0) flip(i,j,m[i][j]);
			else ++cnt;
		}
	dfs(cnt);
	cout<<ans;
}