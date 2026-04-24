#include<bits/stdc++.h>

using namespace std;

int memo[100000] ; 

int tile(int n)
{
	
	if(n < 2)
	{
		return 1;
	}
	
	if(memo[n] != 0)
	{
		return memo[n];
	}
	else
	{
		memo[n] = (tile(n-1)+ tile(n-2))%10007;
	}
	
	return memo[n];
	
}

int main(void)
{
	int n;
	
	cin>>n;
	memo[1] = 1;
	memo[2] = 2;
	cout<<tile(n)<<'\n';
	
	
}