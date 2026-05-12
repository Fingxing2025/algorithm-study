#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double eps=1e-6;
int n;
double a[15];
double f(double x){
	double sum=0;
	for(int i=n;i>=0;--i) sum=sum*x+a[i];
	return sum;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	double l,r;
	cin>>n>>l>>r;
	for(int i=n;i>=0;--i)
		cin>>a[i];
	while(r-l>=eps){
		double k=(r-l)/3.0;
		double m1=l+k,m2=r-k;
		if(f(m1)>f(m2)) r=m2;
		else l=m1;
	}
	cout<<fixed<<setprecision(5)<<l;
}
//枚举，求导二分，优选法