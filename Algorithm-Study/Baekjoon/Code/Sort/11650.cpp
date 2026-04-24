#include <bits/stdc++.h>

using namespace std;


bool cmp(const pair<int , int> &v1, const pair<int, int> &v2)
{
	if(v1.first == v2.first)
	{
		return v1.second < v2.second;
	}
	return v1.first < v2.first;
	
}


int main(void)
{
	int T = 0;
	cin>>T;
	
	vector<pair<int,int>> vec(T);
	int a= 0;
	int b= 0;
	for(int i = 0; i<T; i++)
	{
		cin>>a>>b;
		vec[i].first = a;
		vec[i].second = b;
	}
	
	sort(vec.begin(), vec.end(), cmp);
	
	for(int i = 0; i<T; i++)
	{
		cout<<vec[i].first<<" "<<vec[i].second<<'\n';
	}
	
}
