#include<bits/stdc++.h>

using namespace std;


int main(void)
{
	int N,M,K;
	cin>>N>>M>>K;
	
	int count = 0;
	int best_idx = 0;
	int before_idx = 0;
	
	vector<int> dataSet;
	int result = 0;
	
	int a;
	for(int i = 0; i < N; i++)
	{
		cin>>a;
		dataSet.push_back(a);
	}
	
	sort(dataSet.begin() , dataSet.end());
	
	
	
	/*
	while(true)
	{
		for(int i = 0; i < K; i++)
		{
			if(M == 0)
			{
				break;
			}
			result += dataSet[N-1];
			M -= 1;
		}
		if(M == 0)
		{
			break;
		}
		result += dataSet[N-2];
		M -= 1;
	}
	*/
	
	count = int(M/(K+1)) * K;
	count += M % (K+1);
	
	result += count * dataSet[N-1];
	result += (M-count) * dataSet[N-2];

	
	cout<<result<<endl;
	
	
}