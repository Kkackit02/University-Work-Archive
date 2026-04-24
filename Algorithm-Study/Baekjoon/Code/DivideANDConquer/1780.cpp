#include <bits/stdc++.h>

using namespace std;

int matrix[2400][2400];

string str;

int negativeOne = 0;
int zero = 0;
int positiveOne = 0;

void Divide(int x, int y , int N)
{
	int positiveCount = 0;
	int negativeCount = 0;
	for(int i = x; i < x + N; i++)
	{
		for(int j = y; j < y + N; j++)
		{
			if(matrix[i][j] == 1)
			{
				positiveCount++;
			}
			else if(matrix[i][j] == -1)
			{
				negativeCount++;
			}
		}
	}
	
	if(positiveCount == 0 && negativeCount == 0)
	{
		zero++;
	}
	else if(positiveCount == N*N)
	{
		positiveOne++;
	}
	else if(negativeCount == N*N)
	{
		negativeOne++;
	}
	else
	{
		Divide(x,        y,          N/3);
		Divide(x,        y+N/3,      N/3);
		Divide(x,        y+N/3*2 ,   N/3);
		
		
		Divide(x+N/3 ,   y,          N/3);
		Divide(x+N/3,    y + N/3,    N/3);
		Divide(x+N/3,    y + N/3*2,  N/3);
		
		Divide(x+N/3*2 , y,          N/3);
		Divide(x+N/3*2 , y + N/3,    N/3);
		Divide(x+N/3*2 , y + N/3*2 , N/3);
		
		
	}
	return;
	
}

int main(void)
{
	int N = 0;
	
	memset(matrix, 0, sizeof(matrix));
	
	cin>>N;
	
	for(int i = 0; i<N; i++)
	{
		for(int j = 0; j<N; j++)
		{
			cin>>matrix[i][j];
		}
	}
	
	
	Divide(0,0,N);
	
	printf("%d\n%d\n%d\n", negativeOne , zero, positiveOne);
	
	return 0;
}
