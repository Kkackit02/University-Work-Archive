#include<bits/stdc++.h>

using namespace std;


int main(void)
{
	int N, K;
	
	cin>>N>>K;
	
	
	int input;
	cin>>input;
	
	
	vector<int> v;
	
	
	for(int i = 0; i < N; i++)
	{
		v.push_back(input%10);
		input/=10;
	}
	
	
	for(int i = N-1; i >= 0; i--)
	{
		cout<<v[i];
	}
	cout<<endl;
	
	
	int minNum = -1;
	int minIdx = -1;
	for(int i = 0; i < K; i++)
	{
		minNum = 11;
		for(int j = N-1; j > 0; j--)
		{
			if(minNum < v[j])
			{
				minNum = v[j];
				minIdx = j;
			}
		}
		
		v.erase(v.begin() + minIdx);
	}
	
	for(int i = N-1; i >= 0; i--)
	{
		cout<<v[i];
	}
	cout<<endl;
}