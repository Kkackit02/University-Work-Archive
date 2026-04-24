#include<bits/stdc++.h>
using namespace std;


int main(void)
{
	int N, M;
	
	cin>>N>>M;
	
	int matrix[101][101];
	int result[101];
	
	for(int i =0; i< 101; i++)
	{
		result[i] = 0;
		for(int j = 0; j < 101; j++)
		{
			matrix[i][j] = 0;
		}
	}
	
	int bestidx = 10001;
	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < M; j++)
		{
			cin>>matrix[i][j];
		}
	}
	
	
	for(int i = 0; i < N; i++)
	{
		bestidx = 10001;
		for(int j = 0; j < M; j++)
		{
			if(bestidx >= matrix[i][j])
			{
				bestidx = matrix[i][j];
				result[i] = matrix[i][j];
			}
		}
	}
	
	int bestNum = 0;
	for(int i=0; i<N; i++)
	{
		if(bestNum < result[i])
		{
			bestNum = result[i];
		}
	}
	
	
	printf("%d\n", bestNum);
	
	
}


// 풀이는 맞으나 가장 작은 수, 큰 수를 구하는 std
// VECTOR 이라면 min_element 와 max_element를 
// 그냥 단순한 수나 배열이라면 min, max를 사용했음 어떨까 싶다. 

