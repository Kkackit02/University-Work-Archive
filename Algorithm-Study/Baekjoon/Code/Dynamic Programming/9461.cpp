#include <bits/stdc++.h>

using namespace std;

long long memo[101];

long long Triangle(long long n)
{

	
	if(memo[n] != 0)
	{
		return memo[n];
	}
	else
	{
		memo[n] = (Triangle(n-2) + Triangle(n-3));
		
	}
	
	return (Triangle(n-2) + Triangle(n-3));
}

int main(void)
{
	memo[1] = 1;
	memo[2] = 1;
	memo[3] = 1;
	memo[4] = 2;
	memo[5] = 2;
	memo[6] = 3;
	memo[7] = 4;
	memo[8] = 5;
	memo[9] = 7;
	memo[10] = 9;
	
	int N , T;
	cin>>T;
	
	for(int i = 0; i <T; i++)
	{
		cin>>N;
		Triangle(N);
		cout<<memo[N]<<endl;
		
	}

	return 0;
}

