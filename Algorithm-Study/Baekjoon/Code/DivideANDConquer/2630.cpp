#include <bits/stdc++.h>

using namespace std;

int white = 0;
int blue = 0;

int matrix[129][129];

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
		white++;
	}
	else if(count == N*N)
	{
		blue++;
	}
	else
	{
		Divide(x,y,N/2);
		Divide(x,y+N/2, N/2);
		Divide(x+N/2 , y, N/2);
		Divide(x+N/2,y+N/2, N/2);
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
			scanf("%d" , &matrix[i][j]);
		}
	}
	
	
	Divide(0,0,N);
	
	printf("%d\n%d\n" , white, blue);
	
}
/*
분할정복은 내 사고를 컴퓨팅적 사고로 바꾸지 못하면 어려울 수 밖에 없다.

재귀가 늘 그렇듯이
경우의 수를 따지자.
큰 문제를 최소한의 문제로 쪼개고,
쪼갠 문제를 다시 합치는 과정을 거쳐야한다.

이를 위해서
문제를 쪼개서 경우의 수를 얻으려고 해보자.
*/
