#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int N, M = 0;
	cin>>N>>M;
	char matrix[50][50];
	string text;
	
	int result[50][50];
	memset(result, 0, sizeof(memset));
	
	for(int i = 0; i<N; i++)
	{
		cin>>text;
		for(int j = 0; j<M; j++)
		{
			matrix[j][i] = text[j];
		}
	}
	
	for(int i = 0; i<N; i++)
	{
		for(int j = 0; j<M; j++)
		{
			cout<<matrix[j][i];
			
		}
		cout<<endl;
	}
	
	for(int i = 0; i< N-8; i++)
	{
		for(int j = 0; j< M-8; j++)
		{
			//8x8로 자른 후 확인
			for(int k = 0; k<8; k++)
			{
				for(int l = 0; l < 8; l++)
				{
					if(matrix[])
				}
			}
			
		}
	}
	
}
