#include<bits/stdc++.h>

using namespace std;
//https://www.acmicpc.net/board/view/86573

int month[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; 

int main(void)
{
	int N;
	cin>>N;
	vector<pair<pair<int,int> , pair<int,int>>> v;
	
	
	
	int a, b, c, d;
	for(int i = 0; i < N; i++)
	{
		cin>>a>>b>>c>>d;
		v.push_back(make_pair(make_pair(a,b),make_pair(c,d)));
		
	}
	
	
	sort(v.begin(), v.end());
	
	/*
	for(int i = 0; i < N; i++)
	{
		cout<<v[i].first.first<<":"<<v[i].first.second<<"-";
		cout<<v[i].second.first<<":"<<v[i].second.second<<endl;
	}
	*/
	//first.first = bloom_month
	//first.second = bloom_day
	//second.first = fall_month
	//second.second = fall_day
	
	
	int fall_month = 3;
	int fall_day = 1;
	
	int best_idx = 0;
	
	int result = 0;
	
	int flower_idx = 0;
	
	
	for(int i = best_idx+1; i<N; i++)
	{
			
		if(v[i].first.first < fall_month)
		{
			if(v[best_idx].second.first < v[i].second.first)
			{
				best_idx = i;
				isChecker = true;
			}
			else if(v[best_idx].second.first == v[i].second.first)
			{
				if(v[best_idx].second.second < v[i].second.second)
				{
					best_idx = i;
					isChecker = true;
				}
			}

		}

		else if(v[i].first.first == fall_month)
		{
			if(v[i].first.second <= fall_day)
			{
				if(v[best_idx].second.first < v[i].second.first)
				{
					best_idx = i;
					isChecker = true;
				}
				else if(v[best_idx].second.first == v[i].second.first)
				{
					if(v[best_idx].second.second < v[i].second.second)
					{
						best_idx = i;
						isChecker = true;
					}
				}
			}
		}
	
	}	
	
}