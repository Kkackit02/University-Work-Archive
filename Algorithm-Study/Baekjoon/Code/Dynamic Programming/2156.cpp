#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int N = 0;
	cin>>N;
	
	int input[10001];
	for(int i = 0; i < N; i++)
	{
		cin>>input[i];
	}
	
	vector<int> memo(N+1);
	
	memo[0] = input[0];
	memo[1] = max(input[1] + 0,  input[0] + input[1]);
	memo[2] = max(input[1]+input[2] , input[0] + input[2]);
	
	for(int i = 2; i<N; i++)
	{
		memo[i] = max(max(memo[i-2] + input[i] , memo[i-3] + input[i-1] + input[i]) , memo[i-1]);
	}
	int max = *max_element(memo.begin(), memo.end());
	cout<<max<<'\n';
}

