#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int N = 0;
	cin>>N;
	
	int stair[301];
	for(int i = 0; i < N; i++)
	{
		cin>>stair[i];
	}
	
	vector<int> memo(N+1);
	
	memo[0] = stair[0];
	memo[1] = max(stair[1],  stair[0] + stair[1]);
	memo[2] = max(stair[1]+stair[2] , stair[0] + stair[2]);
	
	for(int i = 3; i<N; i++)
	{
		memo[i] = max(memo[i-2] + stair[i] , memo[i-3] + stair[i-1] + stair[i]);
	}
	
	cout<<memo[N-1]<<'\n';
	/*
	memo[0] = stair[N];
	int i = 1;
	int count = 0;
	int streak = 1;
	while(true)
	{
		if(N-i < 1)
		{
			break;
		}
		if(stair[N-i] > stair[N-i-1])
		{
			if(streak == 2)
			{
				memo[count+1] = stair[N-i-1] + memo[count];
				streak = 0;
				i+=2;
			}
			else
			{
				memo[count+1] = stair[N-i] + memo[count];
				i+=1;
			}
			
			streak++;
				
		}
		else
		{
			memo[count+1] = stair[N-i-1] + memo[count];
			i+=2;
			streak = 0;
		}
		
		count++;
		
	}
	
	
	cout<<memo[count]<<"\n";
	*/
	
	
}

