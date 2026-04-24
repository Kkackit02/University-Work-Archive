#include <bits/stdc++.h>

using namespace std;

long memo[1000001];
int result = 0;

int Tile(int n)
{
	
	if(n == 2)
	{
		return 2; //00 이거나 11이거나
	}
	if(n == 1)
	{
		return 1; //다음 선택이 1인 경우
	}
	if(n == 0)
	{
		return 0;
	}
	
	if(memo[n] != 0)
	{
		return memo[n];
	}
	else
	{
		memo[n] = (Tile(n-1) + Tile(n-2)) % 15746;
		
	}
	
	return (Tile(n-1) + Tile(n-2)) % 15746;
}

int main(void)
{
	int N;
	cin>>N;
	memo[0] = 0;
	memo[1] = 1;
	memo[2] = 2;
	
	Tile(N);
	
	cout<<memo[N]<<endl;
	
	
	return 0;
}

