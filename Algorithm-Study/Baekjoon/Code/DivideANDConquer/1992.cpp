#include <bits/stdc++.h>

using namespace std;

int matrix[65][65];

string str;

void Divide(int x, int y , int N)
{
	int count = 0;
	for(int i = x; i < x + N; i++)
	{
		for(int j = y; j < y + N; j++)
		{
			if(matrix[i][j] == 1)
			{
				count++;
			}
		}
	}
	
	if(count == 0)
	{
		str += "0";
	}
	else if(count == N*N)
	{
		str += "1";
	}
	else
	{
		str += "(";
		Divide(x,y,N/2);
		Divide(x,y+N/2, N/2);
		Divide(x+N/2 , y, N/2);
		Divide(x+N/2,y+N/2, N/2);
		str += ")";
	}
	return;
	
}

int main(void)
{
	int N = 0;
	
	memset(matrix, 0, sizeof(matrix));
	
	cin>>N;
	
	getchar();
	for(int i = 0; i<N; i++)
	{
		for(int j = 0; j<N; j++)
		{
			matrix[i][j] = getchar() - '0';
		}
		getchar();
	}
	
	
	Divide(0,0,N);
	cout<<str<<"\n";
	
}
