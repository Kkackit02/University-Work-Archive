#include<bits/stdc++.h>

using namespace std;
//https://www.acmicpc.net/board/view/86573

int month[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; 

int main(void)
{
	int N;
	cin>>N;
	vector<pair<int,int>> v;
	
	
	
	int a, b, c, d;
	for(int i = 0; i < N; i++)
	{
		cin>>a>>b>>c>>d;
		v.push_back(make_pair(100*a + b, 100*c + b));
		
	}
	
	
	sort(v.begin(), v.end());

	
	int bloom = 301;
	int fall = 1130;
	int best = -1;
	bool isResult = false;
	int result = 0;
	
	for(int i = 0; i < N; i++)
	{
		int bloomDate = v[i].first;
		int fallDate = v[i].second;
		
		if(bloomDate <= bloom)
		{
			best = max(fallDate , best);
			
			if(best > fall)
			{
				isResult = true;
				result++;
				break;
			}
			
		}
		else 
		{
			if(best == -1)
			{
				break;
			}
			
			result++;
			bloom = best;
			best = -1;
			i--;
		}
	}
	
	if(isResult)
	{
		cout<<result<<endl;
	}
	else
	{
		cout<<0<<endl;
	}
}