#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string line,s; vector<string> num;
	getline(cin,line);
	istringstream iss(line);
	while(iss>>s) num.push_back(s);
	sort(num.begin(),num.end(),[](string a,string b){
		return a+b>b+a;
	});
	for(auto t:num) cout<<t;
}