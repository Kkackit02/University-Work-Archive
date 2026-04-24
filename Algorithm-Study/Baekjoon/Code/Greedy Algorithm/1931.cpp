#include <bits/stdc++.h>

using namespace std;


bool cmp(vector<int> &v1, vector<int> &v2){
  	if(v1[1] == v2[1])
  	{
    	return v1[0]<v2[0];
  	}
	else 
	{
		return v1[1]<v2[1];
	}
}


int main(void)
{
	int N = 0;
	cin>>N;
	
	vector<pair<int,int>> meeting;

	
	int a , b;
	for(int i = 0; i<N; i++)
	{
		cin>>a;
		cin>>b;
		meeting.push_back(make_pair(b,a));
		
	}
	
	sort(meeting.begin(), meeting.end());
	
	int time = meeting[0].first;
	
	int count = 1;

	
	
	for(int i = 1; i < N; i++)
	{
		if(time <= meeting[i].second)
		{
			count++;
			time = meeting[i].first;
		}
	}
	
	cout<<count<<'\n';
	
	
	
	
}
