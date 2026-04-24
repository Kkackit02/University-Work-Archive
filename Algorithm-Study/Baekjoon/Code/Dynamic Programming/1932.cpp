#include <bits/stdc++.h>

using namespace std;

int triangle[501][501];


int main(void)
{
	int result = 0;
	int T = 0;
	cin>>T;
	
	for(int i = 0; i<T; i++)
	{
		for(int j = 0; j< i+1; j++)
		{
			cin>>triangle[i][j];
		}
	}

	
	for(int i =0; i< T; i++)
	{
		for(int j =0; j < i+1; j++)
		{
			if(j == 0)
			{
				triangle[i][j] = triangle[i-1][0] + triangle[i][j];
			}
			else if(i == j)
			{
				triangle[i][j] = triangle[i-1][j-1] + triangle[i][j];
			}
			else
			{
				triangle[i][j] = max(triangle[i-1][j-1], triangle[i-1][j]) + triangle[i][j];
			}
			
			
		}
		
	}
	
	
	
	for(int i=0;i<T;i++)
	{
		if(result < triangle[T-1][i])
		{
			result = triangle[T-1][i];
		}
	}
	
	
	cout<<result<<endl;
	
	
	
}
